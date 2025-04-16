// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyAnimCharacter.h"

AEnemyAnimCharacter::AEnemyAnimCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAnimCharacter::ChangeAnimation_Multicast_Implementation(int _CurAnimnation, FName _SectionName)
{
	if (nullptr != EnemyBaseAnimInstance)
	{
		EnemyBaseAnimInstance->ChangeAnimation(_CurAnimnation, _SectionName);
	}
}

void AEnemyAnimCharacter::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* MeshName =  GetMesh();
	EnemyBaseAnimInstance = Cast<UEnemyBaseAnimInstance>(GetMesh()->GetAnimInstance());
}

void AEnemyAnimCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyAnimCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


