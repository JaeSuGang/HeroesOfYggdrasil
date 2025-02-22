// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/YggPawn.h"

AYggPawn::AYggPawn(const FObjectInitializer& ObjectInitializer)
	:
	Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

}

void AYggPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYggPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYggPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

