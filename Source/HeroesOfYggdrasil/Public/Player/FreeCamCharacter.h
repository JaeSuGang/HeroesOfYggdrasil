// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggCharacter.h"
#include "FreeCamCharacter.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class UAttributeComponent;
class UPawnMovementComponent;
class UInputAction;
class UInputMappingContext;
class UInputComponent;
struct FInputActionValue;

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AFreeCamCharacter : public AYggCharacter
{
	GENERATED_BODY()

public:
	AFreeCamCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void BeginPlay() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = YGG)
	UInputMappingContext* DefaultInputMappingContext;

	UPROPERTY(EditAnywhere, Category = YGG)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = YGG)
	UInputAction* MoveAction;
};
