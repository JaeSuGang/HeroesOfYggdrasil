// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGame/MainGameGamemode.h"

AMainGameGamemode::AMainGameGamemode()
{
	DefaultPawnClass = MainPawn;
}

void AMainGameGamemode::BeginPlay()
{
	Super::BeginPlay();
}
