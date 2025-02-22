// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggCharacter.h"
#include "FreeCamPlayer2.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API AFreeCamPlayer2 : public AYggCharacter
{
	GENERATED_BODY()
	
public:
	AFreeCamPlayer2(const FObjectInitializer& objectInitializer = FObjectInitializer::Get());

public:
	void BeginPlay() override;
	void Tick(float fDeltaTime) override;

protected:
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* MappingContext;
};
