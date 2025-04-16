#include "Enemy/EnemyCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Attribute/AttributeComponent.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Attribute/EnemyAttributeComponent.h"

#include "Data/YggStructData.h"
#include "Data/YggConst.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

#include "MainGame/UI/YggMiniMapIconActor.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Component/ActorComponent/Function/TickUtilityFunctionLibrary.h"
#include "Component/ActorComponent/TickDamageComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Component/MHPBarComponent.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Core/YggCharacter.h"
#include "Enemy/EnemyGameInstance.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyProjectile.h"
#include "Enemy/EnemyRangeAttack.h"
#include "Enemy/EnemyWarningRange.h"
#include "Global/YggTickActor.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 기본 속성 및 AI 설정
	CharacterAttributeComponent = CreateDefaultSubobject<UEnemyAttributeComponent>(TEXT("CharacterAttributeComponent"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEnemyAIController::StaticClass();

	// HP 바 위젯 설정
	MHPBarWidgetComponent = CreateDefaultSubobject<UMHPBarComponent>(TEXT("MHPWidgetComponent"));
	MHPBarWidgetComponent->SetupAttachment(GetMesh());
	MHPBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

	TickActorClass = AYggTickActor::StaticClass();

	// 본이 존재할 경우에만 공격 캡슐 생성 및 연결
	auto TryCreateAttackCapsule = [&](FName BoneName, FName CapsuleName, FName MapKey)
		{
			if (GetMesh()->DoesSocketExist(BoneName))
			{
				UYggAttackCapsuleComponent* Capsule = CreateDefaultSubobject<UYggAttackCapsuleComponent>(CapsuleName);
				Capsule->SetupAttachment(GetMesh(), BoneName);
				Capsule->SetOwnerCharacter(this);
				Capsule->SetCollisionProfileName(TEXT("MonsterCollision"));
				AttackCapsuleComponentMap.Add(MapKey, Capsule);
			}
		};

	TryCreateAttackCapsule(TEXT("weapon_r"), TEXT("Right"), TEXT("NormalAttack"));
	TryCreateAttackCapsule(TEXT("MOUNTAIN_DRAGON_-L-Hand"), TEXT("LeftHand"), TEXT("NormalAttack"));
	TryCreateAttackCapsule(TEXT("MOUNTAIN_DRAGON_-R-Hand"), TEXT("RightHand"), TEXT("NormalAttack"));
}

void AEnemyCharacter::BeginPlay()
{
	// 몬스터 데이터 키가 비었는지 확인
	if (DataKey.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> EnemyDataKey is empty"), __FUNCTION__, __LINE__);
		return;
	}

	// 데이터 테이블에서 몬스터 데이터 조회
	const FMonsterDataRow FindData = UGlobalDataTable::GetMonsterData(GetWorld(), DataKey);
	MonsterData = &FindData;

	AEnemyAIController* Con = Cast<AEnemyAIController>(GetController());

	// AI 데이터 생성 및 설정
	AIData = NewObject<UAIDataObject>(this);
	if (AIData)
	{
		AIData->PlayData.Data = FindData.AIData;
		AIData->PlayData.SelfPawn = this;
		AIData->PlayData.SelfAnimPawn = this;
		AIData->PlayData.CurHP = FindData.AIData.MaxHP;
		AIData->PlayData.OriginPos = GetActorLocation();
		AIData->PlayData.OriginPos.Z = 0.0f;
	}

	// 블랙보드에 AI 데이터 바인딩
	if (Con)
	{
		Con->GetBlackboardComponent()->SetValueAsObject(TEXT("EnemyAIData"), AIData);
	}

	// 메시 설정 및 애님 블루프린트 바인딩
	GetMesh()->SetCollisionProfileName("MonsterCollision");
	GetMesh()->SetSkeletalMesh(FindData.Mesh);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(FindData.AnimationBluePrint);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetSimulatePhysics(false);

	// 애님 인스턴스 가져와서 몽타주 등록
	UEnemyBaseAnimInstance* NewEnemyAnimInstance = Cast<UEnemyBaseAnimInstance>(GetMesh()->GetAnimInstance());
	if (NewEnemyAnimInstance)
	{
		for (auto AnimPair : FindData.Animations)
		{
			NewEnemyAnimInstance->AnimMontages.Add(static_cast<int>(AnimPair.Key), AnimPair.Value);
		}
		if (Con)
		{
			AIData->PlayData.UEnemyBaseAnimInstance = NewEnemyAnimInstance;
		}
	}

	// 이동 설정
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 450.0f;

	Super::BeginPlay();

	// 틱 관련 파티클 시스템 저장
	TickParticle = FindData.TickParticle;
	TickNiagaraSystem = FindData.TickNiagaraSystem;

	// 속성 컴포넌트 설정 및 초기화
	if (CharacterAttributeComponent && HasAuthority())
	{
		CharacterAttributeComponent->Server_SetHP(AIData->PlayData.CurHP);
		CharacterAttributeComponent->Server_SetMaxHP(MonsterData->AIData.MaxHP);
		CharacterAttributeComponent->Server_SetAttackPoints(MonsterData->AIData.EnemyAttackPoints);
		CharacterAttributeComponent->Server_SetDefensePoints(MonsterData->AIData.EnemyDefensePoints);
		CharacterAttributeComponent->AddTag(TEXT("Enemy"));
		SetActorScale3D(MonsterData->AIData.Scale);
		OnHeroEnteredRange.AddDynamic(this, &AEnemyCharacter::HandleHeroEnteredRange);
	}

	// HP 바 위젯 초기화
	MHPBarWidgetComponent->Init(this);

	// 캡슐 컴포넌트 충돌 바인딩
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OverLap);

	// 미니맵 아이콘 생성 및 연결
	MiniMapIcon = GetWorld()->SpawnActor<AYggMiniMapIconActor>(MiniMapIconClass);
	MiniMapIcon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	MiniMapIcon->SetPaperSprite(FName("Monster"));
	MiniMapIcon->SetAttachedCharacter(this);
	MiniMapIcon->AddToCaptureComponent();
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 체력 정보 실시간 동기화
	if (IsValid(AIData) && IsValid(CharacterAttributeComponent))
	{
		AIData->PlayData.CurHP = CharacterAttributeComponent->HP;
	}
}



void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyCharacter, DataKey);
}

void AEnemyCharacter::OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AEnemyCharacter::AttackStart()
{
	GetMesh()->SetCollisionProfileName(UEnemyConst::Collision::ProfileName_MonsterAttack);
}

void AEnemyCharacter::AttackEnd()
{
	GetMesh()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

void AEnemyCharacter::DestroyAllComponents()
{
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Component : Components)
	{
		if (IsValid(Component))
		{
			Component->DestroyComponent();
		}
	}

	if (MiniMapIcon)
	{
		MiniMapIcon->Destroy();
	}

	Destroy();
}

void AEnemyCharacter::SetDataKey(const FString& _MonsterDataKey)
{
	DataKey = _MonsterDataKey;
}

void AEnemyCharacter::SpawnAndFireArrow()
{
	if (!ProjectileClass) return;

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 150.0f + GetActorUpVector() * 50.0f;
	FRotator SpawnRotation = GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	AEnemyProjectile* Arrow = GetWorld()->SpawnActor<AEnemyProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (Arrow)
	{
		Arrow->SetAttackFloat(CharacterAttributeComponent->AttackPoints);
		Arrow->GetProjectileMovement()->Velocity = GetActorForwardVector() * 2000.f;
	}
}

void AEnemyCharacter::HideArrow()
{
	GetMesh()->HideBoneByName(FName("arrow_nock"), EPhysBodyOp::PBO_None);
}

void AEnemyCharacter::RevealArrow()
{
	GetMesh()->UnHideBoneByName(FName("arrow_nock"));
}

void AEnemyCharacter::SpawnWarningRange(AActor* _Actor)
{
	SpawnWarningOutRange(_Actor);
}

void AEnemyCharacter::SpawnWarningOutRange(AActor* _Actor)
{
	if (!WarningOutRangeClass || !_Actor) return;

	UCapsuleComponent* Capsule = _Actor->FindComponentByClass<UCapsuleComponent>();
	FVector SpawnLocation = _Actor->GetActorLocation();

	if (Capsule)
	{
		SpawnLocation -= FVector(0, 0, Capsule->GetScaledCapsuleHalfHeight());
	}

	FRotator SpawnRotation = _Actor->GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	GetWorld()->SpawnActor<AEnemyWarningRange>(WarningOutRangeClass, SpawnLocation, SpawnRotation, SpawnParams);
}

void AEnemyCharacter::SpawnEnemySkillAttack(FVector _TargetLocation)
{
	if (!RangeAttackClass) return;

	FVector SpawnLocation = GetActorLocation() + GetActorRightVector() * -50.0f + GetActorUpVector() * 50.0f;
	FRotator SpawnRotation = GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	AEnemyRangeAttack* RangeAttack = GetWorld()->SpawnActor<AEnemyRangeAttack>(RangeAttackClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (RangeAttack)
	{
		RangeAttack->SetOwner(this);
		RangeAttack->GetProjectileMovement()->Velocity = (_TargetLocation - SpawnLocation).GetSafeNormal() * 2000.f;
	}
}

void AEnemyCharacter::HandleHeroEnteredRange(AYggCharacter* _Target)
{
	if (!HasAuthority()) return;

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(_Target);
	AYggHero* Hero = Cast<AYggHero>(_Target);
	if (!IsValid(Hero) && !IsValid(Enemy)) return;

	float Damage = CharacterAttributeComponent->AttackPoints / 10.0f;
	AYggTickActor::SpawnTickEffectIfNotExist(this, _Target);
}
