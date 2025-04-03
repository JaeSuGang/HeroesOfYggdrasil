

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

#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "AIController.h"

#include "Enemy/EnemyGameInstance.h"
#include "MainGame/UI/YggMiniMapIconActor.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyProjectile.h"
#include "Enemy/EnemyRangeAttack.h"
#include "Enemy/EnemyWarningRange.h"

#include "Components/WidgetComponent.h"
#include "MainGame/UI/YggMHPBarUserWidget.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CharacterAttributeComponent = CreateDefaultSubobject<UEnemyAttributeComponent>(TEXT("CharacterAttributeComponent"));
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEnemyAIController::StaticClass();
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());
	WidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	{
		UYggAttackCapsuleComponent* AttackCapsule = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("Right"));
		AttackCapsule->SetupAttachment(GetMesh(),TEXT("weapon_r"));
		AttackCapsuleComponentMap.Add(TEXT("NormalAttack"), AttackCapsule);

	}
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

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	UEnemyBaseAnimInstance* NewEnemyAnimInstance = Cast<UEnemyBaseAnimInstance>(AnimInstance);

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




	// AttributeComponent 세팅
	if (CharacterAttributeComponent != nullptr && Con != nullptr)
	{
		CharacterAttributeComponent->Server_SetHP(AIData->PlayData.CurHP);
		CharacterAttributeComponent->Server_SetMaxHP(MonsterData->AIData.MaxHP);
		CharacterAttributeComponent->Server_SetAttackPoints(MonsterData->AIData.EnemyAttackPoints);
		CharacterAttributeComponent->Server_SetDefensePoints(MonsterData->AIData.EnemyDefensePoints);
		
		// 위젯
		MHPBarUserWidget = CreateWidget<UYggMHPBarUserWidget>(GetWorld(), MHPBarUserWidgetClass);
	
		if (!MHPBarUserWidget)
			UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
		MHPBarUserWidget->SetAttachedCharacter(this);
		WidgetComponent->SetWidget(MHPBarUserWidget);
	}

	// 충돌 설정
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OverLap);
	if (CharacterAttributeComponent != nullptr)
	{
		CharacterAttributeComponent->ClientDelegate_OnTakeDamage.AddDynamic(MHPBarUserWidget, &UYggMHPBarUserWidget::UpdateHPBar);
	}


	AYggMiniMapIconActor* MiniMapIcon = GetWorld()->SpawnActor<AYggMiniMapIconActor>(MiniMapIconClass);
	MiniMapIcon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	MiniMapIcon->SetPaperSprite(FName("Monster"));
	MiniMapIcon->SetAttachedCharacter(this);
	MiniMapIcon->AddToCaptureComponent();

	
	
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
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
	/*AYggCharacter* HeroCharacter = Cast<AYggCharacter>(OtherActor);
	UCharacterAttributeComponent * HeroCharacterAttributeComponent = HeroCharacter->GetComponentByClass<UCharacterAttributeComponent>();
	float HeroAttackPoints = HeroCharacterAttributeComponent->GetAttackPoints();

	AIData->PlayData.CurHP -= HeroAttackPoints;*/
	//MHPBarUserWidget->UpdateHPBar(HeroAttackPoints);
}

void AEnemyCharacter::AttackStart()
{
	if (this != nullptr)
	{
		GetMesh()->SetCollisionProfileName(UEnemyConst::Collision::ProfileName_MonsterAttack);
	}
}

void AEnemyCharacter::AttackEnd()
{
	if (this != nullptr)
	{
		GetMesh()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	}
}


// 궁수 화살 발사

void AEnemyCharacter::SpawnAndFireArrow()
{
	if (ProjectileClass == nullptr)
	{
		return;
	}

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 150.0f + GetActorUpVector() * 50.0f;
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	AEnemyProjectile* Arrow = GetWorld()->SpawnActor<AEnemyProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (Arrow != nullptr)
	{
		FVector LaunchDirection = GetActorForwardVector();
		Arrow->GetProjectileMovement()->Velocity = LaunchDirection * 2000.f;
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



// 저주술사 


// 위험 범위
void AEnemyCharacter::SpawnWarningRange(AActor* _Actor)
{
	SpawnWarningOutRange(_Actor);
	SpawnWarningInRange(_Actor);
}

void AEnemyCharacter::SpawnWarningOutRange(AActor* _Actor)
{
	if (!WarningOutRangeClass || !_Actor)
		return;

	UCapsuleComponent* Capsule = _Actor->FindComponentByClass<UCapsuleComponent>();
	FVector SpawnLocation = _Actor->GetActorLocation();

	if (Capsule)
	{
		float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();
		SpawnLocation -= FVector(0, 0, HalfHeight);
	}

	FRotator SpawnRotation = _Actor->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	GetWorld()->SpawnActor<AEnemyWarningRange>(
		WarningOutRangeClass, SpawnLocation, SpawnRotation, SpawnParams);
}

void AEnemyCharacter::SpawnWarningInRange(AActor* _Actor)
{
	if (!WarningInRangeClass || !_Actor)
		return;

	UCapsuleComponent* Capsule = _Actor->FindComponentByClass<UCapsuleComponent>();
	FVector SpawnLocation = _Actor->GetActorLocation();

	if (Capsule)
	{
		float HalfHeight = Capsule->GetScaledCapsuleHalfHeight();
		SpawnLocation -= FVector(0, 0, HalfHeight);
	}

	FRotator SpawnRotation = _Actor->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	
	WarningInRangeClass = GetWorld()->SpawnActor<AEnemyWarningRange>(AEnemyWarningRange::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
}

// 공격

void AEnemyCharacter::ThrowPoisonedBall(FVector _TargetLocation)
{
	if (RangeAttackClass == nullptr)
	{
		return;
	}

	FVector SpawnLocation = GetActorLocation() + GetActorRightVector() * -50.0f + GetActorUpVector() * 50.0f;
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	AEnemyRangeAttack* RangeAttack = GetWorld()->SpawnActor<AEnemyRangeAttack>(RangeAttackClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (RangeAttack != nullptr)
	{
		const float Speed = 2000.f;
		FVector Direction = (_TargetLocation - SpawnLocation).GetSafeNormal();
		RangeAttack->GetProjectileMovement()->Velocity = Direction * Speed;
	}
}

