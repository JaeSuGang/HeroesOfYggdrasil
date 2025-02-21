// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/YggPawn.h"
#include "FreeCamPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UAttributeComponent;
class UInputAction;
class UInputMappingContext;
class UInputComponent;
struct FInputActionValue;

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AFreeCamPawn : public AYggPawn
{
	GENERATED_BODY()

public:
	AFreeCamPawn(const FObjectInitializer& objectInitializer);

protected:
	void NotifyControllerChanged() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void Look(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere)
	UAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = YGG)
	UInputMappingContext* DefaultInputMappingContext;

	UPROPERTY(EditAnywhere, Category = YGG)
	UInputAction* LookAction;
};
