// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "TestPlayerController_kjhg.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API ATestPlayerController_kjhg : public APlayerController
{
	GENERATED_BODY()
	
protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

protected:
    void Look(const FInputActionValue& _Value);
    void Move(const FInputActionValue& _Value);
    void Jump(const FInputActionValue& _Value);
    void Attack(const FInputActionValue& _Value);

public:
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputMappingContext* InputMappingContext;
    
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* JumpAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* AttackAction;

};
