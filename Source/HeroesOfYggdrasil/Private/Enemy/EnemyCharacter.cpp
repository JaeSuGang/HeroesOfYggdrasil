

#include "Enemy/EnemyCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Data/YggStructData.h"
#include "Enemy/EnemyAIController.h"
#include "Net/UnrealNetwork.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/EnemyGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Attribute/EnemyAttributeComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	EnemyAttributeComponent = CreateDefaultSubobject<UEnemyAttributeComponent>(TEXT("AttributeComponent"));
}

void AEnemyCharacter::BeginPlay()
{
	if (DataKey == TEXT("") || true == DataKey.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (ItemDataKey == TEXT("") || true == ItemDataKey.IsEmpty())"), __FUNCTION__, __LINE__);
		return;
	}

	const FMonsterDataRow FindData = UGlobalDataTable::GetMonsterData(GetWorld(), DataKey);
	MonsterData = &FindData;
	AEnemyAIController* Con = Cast<AEnemyAIController>(GetController());


	if (nullptr != Con)
	{
		AIData = NewObject<UAIDataObject>(this);
		AIData->PlayData.Data = FindData.AIData;
		AIData->PlayData.SelfPawn = this;
		AIData->PlayData.SelfAnimPawn = this;
		AIData->PlayData.CurHP = FindData.AIData.MaxHP;
		// AIData->PlayData.AttackAnimationCount = FindData.AttackAnimations.Num();
		AIData->PlayData.OriginPos = GetActorLocation();
		Con->GetBlackboardComponent()->SetValueAsObject(TEXT("EnemyAIData"), AIData);
	}

	GetMesh()->SetSkeletalMesh(FindData.Mesh);
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(FindData.AnimationBluePrint);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	UEnemyBaseAnimInstance* NewEnemyAnimInstance = Cast<UEnemyBaseAnimInstance>(AnimInstance);

	if (nullptr != NewEnemyAnimInstance)
	{
		for (auto AnimPair : FindData.Animations)
		{
			NewEnemyAnimInstance->AnimMontages.Add(static_cast<int>(AnimPair.Key), AnimPair.Value);
		}

		for (size_t i = 0; i < FindData.AttackAnimations.Num(); i++)
		{
			UAnimMontage* Montage = FindData.AttackAnimations[i];
			NewEnemyAnimInstance->AnimMontages.Add(100 + i, Montage);
		}

		if (nullptr != Con)
		{
			AIData->PlayData.UEnemyBaseAnimInstance = NewEnemyAnimInstance;
		}

	}


	Super::BeginPlay();
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
	int a = 0;
}
