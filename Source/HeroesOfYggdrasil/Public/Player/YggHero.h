// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggCharacter.h"
#include "YggHero.generated.h"

/**
 * 김성훈
 * 히어로 기본 클래스
 */


// Camera
class USpringArmComponent;
class UCameraComponent;

// Input
class UInputMappingContext;
class UInputAction;
class UInputComponent;
struct FInputActionValue;

UCLASS()
class HEROESOFYGGDRASIL_API AYggHero : public AYggCharacter
{
	GENERATED_BODY()
public:
	AYggHero();
protected:

	virtual void Look(const FInputActionValue& _Value);
	virtual void Move(const FInputActionValue& _Value);

	virtual void Attack(const FInputActionValue& _Value){}
	virtual void SkillQ(const FInputActionValue& _Value){}
	virtual void SkillE(const FInputActionValue& _Value){}
	virtual void SkillR(const FInputActionValue& _Value){}

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* AttackAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SkillQAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SkillEAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* SkillRAction;

};
