// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/YggPawn.h"

// Sets default values
AYggPawn::AYggPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
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

