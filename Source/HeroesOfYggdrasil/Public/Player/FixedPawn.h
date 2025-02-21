// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/YggPawn.h"
#include "FixedPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UAttributeComponent;

/**
 * ´ã´ç : ±è°æ¹Î
 */
UCLASS()
class HEROESOFYGGDRASIL_API AFixedPawn : public AYggPawn
{
	GENERATED_BODY()
	
public:
	AFixedPawn(const FObjectInitializer& objectInitializer);

public:
	UPROPERTY(EditAnywhere)
	UAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
};
