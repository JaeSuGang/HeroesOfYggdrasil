

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
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Attribute/EnemyAttributeComponent.h"
#include "MainGame/UI/YggMiniMapIconActor.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyProjectile.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CharacterAttributeComponent = CreateDefaultSubobject<UEnemyAttributeComponent>(TEXT("CharacterAttributeComponent"));
	EnemyAttributeComponent = Cast<UEnemyAttributeComponent>(CharacterAttributeComponent);
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEnemyAIController::StaticClass();
}

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

		// AIData->PlayData.AttackAnimationCount = FindData.AttackAnimations.Num();
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
	if (EnemyAttributeComponent != nullptr && Con != nullptr)
	{
		//EnemyAttributeComponent->Server_SetHP(AIData->PlayData.CurHP);
		EnemyAttributeComponent->Server_SetMaxHP(MonsterData->AIData.MaxHP);
		EnemyAttributeComponent->Server_SetAttackPoints(MonsterData->AIData.EnemyAttackPoints);
		EnemyAttributeComponent->Server_SetDefensePoints(MonsterData->AIData.EnemyDefensePoints);
	}

	// 충돌 설정
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OverLap);

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
	AYggCharacter* HeroCharacter = Cast<AYggCharacter>(OtherActor);
	UCharacterAttributeComponent * HeroCharacterAttributeComponent = HeroCharacter->GetComponentByClass<UCharacterAttributeComponent>();
	float HeroAttackPoints = HeroCharacterAttributeComponent->GetAttackPoints();


	EnemyAttributeComponent->Server_TakeDamage(HeroAttackPoints);
	AIData->PlayData.CurHP -= HeroAttackPoints;
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
