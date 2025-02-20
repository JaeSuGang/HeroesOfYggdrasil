// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/YggPawn.h"
#include "FixedPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * ´ã´ç : ±è°æ¹Î
 */
UCLASS()
class HEROESOFYGGDRASIL_API AFixedPawn : public AYggPawn
{
	GENERATED_BODY()
	
public:
	UCameraComponent* CameraComponent;

};
