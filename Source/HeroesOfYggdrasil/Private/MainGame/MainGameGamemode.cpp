// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGame/MainGameGamemode.h"

AMainGameGamemode::AMainGameGamemode()
{
	DefaultPawnClass = MainPawn;
}

void AMainGameGamemode::PostLogin(APlayerController* PC)
{
	Super::PostLogin(PC);

	FVector FinalSelectZoneLocation = SelectZoneLocation;
	FinalSelectZoneLocation += SelectZonePosOffset * (GetNumPlayers() - 1);
	FActorSpawnParameters SpawnParams{};
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(SelectZone, FinalSelectZoneLocation, SelectZoneRotation, SpawnParams);
}

void AMainGameGamemode::BeginPlay()
{
	Super::BeginPlay();


}
