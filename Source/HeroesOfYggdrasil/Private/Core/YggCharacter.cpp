// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/YggCharacter.h"

// Sets default values
AYggCharacter::AYggCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYggCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYggCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AYggCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

