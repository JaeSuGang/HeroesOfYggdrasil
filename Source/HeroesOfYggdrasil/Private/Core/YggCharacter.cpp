// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/YggCharacter.h"

AYggCharacter::AYggCharacter(const FObjectInitializer& ObjectInitializer)
	:
	Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

