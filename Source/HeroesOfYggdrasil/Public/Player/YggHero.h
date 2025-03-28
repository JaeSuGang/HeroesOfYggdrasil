// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggCharacter.h"

#include "YggHero.generated.h"

/**
 * 김성훈, 김지호
 * 히어로 기본 클래스
 */


 // Unreal Engine Core
class APlayerController;
 // Camera

class USpringArmComponent;
class UCameraComponent;
class UCaptureComponent;

// Input
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class UEnhancedInputComponent;
struct FInputActionValue;

// Animation
class UYggHeroAnimInstance;

// Attribute
class UHeroAttributeComponent;

// UI
class UWidgetComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AYggHero : public AYggCharacter
{
	GENERATED_BODY()
public:
	AYggHero();
	UFUNCTION(BlueprintCallable)
	UHeroAttributeComponent* GetHeroAttributeComponent()
	{
		return HeroAttributeComponent;
	}

	UFUNCTION(BlueprintCallable)
	UYggHeroAnimInstance* GetHeroAnimInstance()
	{
		return HeroAnimInstance;
	}

	UFUNCTION(BlueprintCallable)
	UInputMappingContext* GetInputMappingContext()
	{
		return InputMappingContext;
	}

	UFUNCTION(BlueprintCallable)
	UCaptureComponent* GetFaceCaptureComponent()
	{
		return FaceCaptureComponent;
	}

	UFUNCTION(BlueprintCallable)
	UCaptureComponent* GetMiniMapCaptureComponent()
	{
		return MiniMapCaptureComponent;
	}

	UFUNCTION(NetMulticast, Reliable)
	void TakeDamageEffect(float Att);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Look(const FInputActionValue& Value);
	virtual void Move(const FInputActionValue& Value);
	virtual void Jump() override;

	virtual void Roll(const FInputActionValue& Value);
	UFUNCTION(Server, Reliable)
	void ServerRoll(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRoll(const FInputActionValue& Value);

	virtual void Attack(const FInputActionValue& Value) {}
	virtual void EndAttack(const FInputActionValue& Value) {}
	virtual void SkillQ(const FInputActionValue& Value) {}
	virtual void SkillE(const FInputActionValue& Value) {}
	virtual void SkillR(const FInputActionValue& Value) {}

	virtual void ToggleAimMode();
	virtual void SetAimMode(bool Value);

	virtual void UpdateStatus();

	virtual void CameraZoomInOut(const FInputActionValue& Value);
	virtual void ToggleUIMode();
	virtual void SetUIMode(bool Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggCamera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggCamera")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "YggInput")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "YggInput")
	TMap<FName, UInputAction*> ActionMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "YggAnimation")
	UYggHeroAnimInstance* HeroAnimInstance;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "YggAttribute")
	UHeroAttributeComponent* HeroAttributeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggTimeEvent")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggCamera")
	UCaptureComponent* FaceCaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggCamera")
	UCaptureComponent* MiniMapCaptureComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bAimMode = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsUIMode = false;

protected:

};
