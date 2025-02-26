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

	UFUNCTION(Server, Reliable)
	void ToggleAimMode();

	UFUNCTION(Server, Reliable)
	void SetAimMode(bool Value);

	UFUNCTION()
	bool GetAimMode()
	{
		return bAimMode;
	}

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	virtual void Look(const FInputActionValue& Value);
	virtual void Move(const FInputActionValue& Value);

	virtual void Attack(const FInputActionValue& Value){}
	virtual void SkillQ(const FInputActionValue& Value){}
	virtual void SkillE(const FInputActionValue& Value){}
	virtual void SkillR(const FInputActionValue& Value){}

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<FName,UInputAction*> ActionMap;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, replicated)
	bool bAimMode = false;
};
