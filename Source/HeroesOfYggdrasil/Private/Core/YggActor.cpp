// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/YggActor.h"

AYggActor::AYggActor(const FObjectInitializer& ObjectInitializer)
	:
	Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

// Called when the game starts or when spawned
void AYggActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYggActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

