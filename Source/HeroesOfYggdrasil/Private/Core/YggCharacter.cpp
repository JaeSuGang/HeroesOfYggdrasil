// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/YggCharacter.h"

#include "Component/SceneComponent/YggCapsuleComponent.h"

#include "Net/UnrealNetwork.h"

AYggCharacter::AYggCharacter(const FObjectInitializer& ObjectInitializer)
	:
	Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

void AYggCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AYggCharacter, CharacterAttributeComponent);
}

UYggCapsuleComponent* AYggCharacter::GetAttackCapsuleComponent(const FName& Key)
{
	if (AttackCapsuleComponentMap.Contains(Key))
	{
		return AttackCapsuleComponentMap[Key];
	}
	return nullptr;
}

