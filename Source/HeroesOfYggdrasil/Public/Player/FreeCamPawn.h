// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/YggPawn.h"
#include "FreeCamPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UAttributeComponent;
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

//protected:
//	void Move(const FInputActionValue& Value);
//
//	void Look(const FInputActionValue& Value);
//
//
//protected:
//
//	virtual void NotifyControllerChanged() override;
//
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//

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
