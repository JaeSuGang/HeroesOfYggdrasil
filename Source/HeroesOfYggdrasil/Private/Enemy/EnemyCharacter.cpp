#include "Enemy/EnemyCharacter.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Attribute/AttributeComponent.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Attribute/EnemyAttributeComponent.h"

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


	RightAttackCapsule = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("RightAttackCapsule"));
	LeftAttackCapsule = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("LeftAttackCapsule"));
}

void AEnemyCharacter::BeginPlay()
{
	if (DataKey == TEXT("") || true == DataKey.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (EnemyDataKey == TEXT("") || true == EnemyDataKey.IsEmpty())"), __FUNCTION__, __LINE__);
		return;
	}

	const FMonsterDataRow FindData = UGlobalDataTable::GetMonsterData(GetWorld(), DataKey);
	MonsterData = &FindData;
	EnemyType = ConvertStringToEnemyType(DataKey);


	AEnemyAIController* Con = Cast<AEnemyAIController>(GetController());

	AIData = NewObject<UAIDataObject>(this);
	if (AIData != nullptr)
	{
		AIData->PlayData.Data = FindData.AIData;
		AIData->PlayData.SelfPawn = this;
		AIData->PlayData.SelfAnimPawn = this;
		AIData->PlayData.CurHP = FindData.AIData.MaxHP;
		AIData->PlayData.OriginPos = GetActorLocation();
		AIData->PlayData.OriginPos.Z = 0.0f;

	}

	// 몬스터 데이터 세팅
	if (nullptr != Con)
	{
		Con->GetBlackboardComponent()->SetValueAsObject(TEXT("EnemyAIData"), AIData);
	}


	// 메시 세팅
	GetMesh()->SetCollisionProfileName("MonsterCollision");
	GetMesh()->SetSkeletalMesh(FindData.Mesh);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(FindData.AnimationBluePrint);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetSimulatePhysics(false);

	USkeletalMeshComponent* SkelMesh = GetMesh();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	UEnemyBaseAnimInstance* NewEnemyAnimInstance = Cast<UEnemyBaseAnimInstance>(AnimInstance);
	

	AttackCollisionInit();
	
	


	// 애니메이션 세팅
	if (nullptr != NewEnemyAnimInstance)
	{
		for (auto AnimPair : FindData.Animations)
		{
			NewEnemyAnimInstance->AnimMontages.Add(static_cast<int>(AnimPair.Key), AnimPair.Value);
		}

		if (nullptr != Con)
		{
			AIData->PlayData.UEnemyBaseAnimInstance = NewEnemyAnimInstance;
		}

	}

	// 무브넌트 컴포넌트 세팅
	GetCharacterMovement()->bUseRVOAvoidance = true;
	GetCharacterMovement()->AvoidanceConsiderationRadius = 450.0f;

	Super::BeginPlay();


	TickParticle = FindData.TickParticle;
	TickNiagaraSystem = FindData.TickNiagaraSystem;


	// AttributeComponent 세팅
	if (CharacterAttributeComponent != nullptr)
	{
		if (HasAuthority())
		{
			CharacterAttributeComponent->Server_SetHP(AIData->PlayData.CurHP);
			CharacterAttributeComponent->Server_SetMaxHP(MonsterData->AIData.MaxHP);
			CharacterAttributeComponent->Server_SetAttackPoints(MonsterData->AIData.EnemyAttackPoints);
			CharacterAttributeComponent->Server_SetDefensePoints(MonsterData->AIData.EnemyDefensePoints);
			CharacterAttributeComponent->AddTag(TEXT("Enemy"));
			SetActorScale3D(MonsterData->AIData.Scale);
			OnHeroEnteredRange.AddDynamic(this, &AEnemyCharacter::HandleHeroEnteredRange);
		}
	}


	MHPBarWidgetComponent->Init(this);

	// 충돌 설정
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OverLap);

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

void AEnemyCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 타이머 정리
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}


void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEnemyCharacter, DataKey);
	DOREPLIFETIME(AEnemyCharacter, EnemyType);
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
	EStatusEffectType Effect = UTickUtilityFunctionLibrary::FindStatusEffectType(this);
	AYggTickActor::SpawnTickEffectIfNotExist(this, _Target, Effect);
}

void AEnemyCharacter::AttackCollisionInit()
{
	// 콜리전 설정
	RightAttackCapsule->SetOwnerCharacter(this);
	RightAttackCapsule->SetCollisionProfileName(TEXT("MonsterAttackCollision"));
	AttackCapsuleComponentMap.Add(TEXT("NormalAttack"), RightAttackCapsule);

	LeftAttackCapsule->SetOwnerCharacter(this);
	LeftAttackCapsule->SetCollisionProfileName(TEXT("MonsterAttackCollision"));
	AttackCapsuleComponentMap.Add(TEXT("NormalAttack"), LeftAttackCapsule);

	// 오른손 소켓에 부착
	if (GetMesh() && GetMesh()->DoesSocketExist(TEXT("MOUNTAIN_DRAGON_-R-Hand")))
	{
		RightAttackCapsule->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("MOUNTAIN_DRAGON_-R-Hand")
		);
		RightAttackCapsule->SetCapsuleSize(300.0f, 200.0f); // (Radius, HalfHeight)
	}
	else if (GetMesh() && GetMesh()->DoesSocketExist(TEXT("weapon_r")))
	{
		RightAttackCapsule->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("weapon_r")
		);
		RightAttackCapsule->SetCapsuleSize(100.0f, 100.0f);
	}
	else
	{
		RightAttackCapsule->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform
		);
	}

	// 왼손 소켓에 부착
	if (GetMesh() && GetMesh()->DoesSocketExist(TEXT("MOUNTAIN_DRAGON_-L-Hand")))
	{
		LeftAttackCapsule->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("MOUNTAIN_DRAGON_-L-Hand")
		);
		LeftAttackCapsule->SetCapsuleSize(300.0f, 200.0f);
	}
	else if (GetMesh() && GetMesh()->DoesSocketExist(TEXT("weapon_l")))
	{
		LeftAttackCapsule->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("weapon_l")
		);
		LeftAttackCapsule->SetCapsuleSize(100.0f, 100.0f);
	}
	else
	{
		LeftAttackCapsule->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::KeepRelativeTransform
		);
	}
}


void AEnemyCharacter::DragonRangeAttack(AActor* _Actor)
{
	if (!WarningOutRangeClass || !_Actor) return;

	UCapsuleComponent* Capsule = _Actor->FindComponentByClass<UCapsuleComponent>();
	FVector BaseLocation = GetActorLocation();
	float ZOffset = Capsule ? Capsule->GetScaledCapsuleHalfHeight() : 0.f;
	ZOffset *= 2.0f;
	const int NumToSpawn = 10;
	const float Radius = 1500.f;

	for (int i = 0; i < NumToSpawn; ++i)
	{
		// 각 위치값 미리 계산
		float Angle = FMath::RandRange(0.f, 360.f);
		float Distance = FMath::RandRange(Radius * 0.5f, Radius);
		float X = FMath::Cos(FMath::DegreesToRadians(Angle)) * Distance;
		float Y = FMath::Sin(FMath::DegreesToRadians(Angle)) * Distance;
		FVector SpawnLocation = BaseLocation + FVector(X, Y, -ZOffset);

		// 랜덤한 딜레이 시간 (0~3초)
		float Delay = FMath::FRandRange(0.f, 3.f);

		// 타이머 바인딩용 로컬 복사 변수
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindLambda([this, SpawnLocation, _Actor]()
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				GetWorld()->SpawnActor<AEnemyWarningRange>(WarningOutRangeClass, SpawnLocation, _Actor->GetActorRotation(), SpawnParams);
			});

		// 타이머로 예약
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, Delay, false);
	}
}

EEnemyType AEnemyCharacter::ConvertStringToEnemyType(const FString& EnemyKey)
{
	if (EnemyKey.StartsWith(TEXT("Minion_Melee")))
	{
		return EEnemyType::Minion_Melee;
	}
	else if (EnemyKey.StartsWith(TEXT("Minion_Archer")))
	{
		return EEnemyType::Minion_Archer;
	}
	else if (EnemyKey.StartsWith(TEXT("Minion_Witch")))
	{
		return EEnemyType::Minion_Witch;
	}
	else if (EnemyKey.StartsWith(TEXT("Dragon")))
	{
		return EEnemyType::Dragon;
	}

	return EEnemyType::Unknown;
}
