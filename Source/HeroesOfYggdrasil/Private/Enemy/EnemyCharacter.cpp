

#include "Enemy/EnemyCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	EnemyAttributeComponent = CreateDefaultSubobject<UCharacterAttributeComponent>(TEXT("AttributeComponent"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// EnemyAttributeComponent->AddTag(TEXT("Monster.State.Strafing"));
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

