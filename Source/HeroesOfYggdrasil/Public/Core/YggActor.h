// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YggActor.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AYggActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AYggActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
