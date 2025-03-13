// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggCharacter.h"
#include "YggHero.generated.h"

/**
 * 김성훈, 김지호
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

// Animation
class UYggHeroAnimInstance;

// Attribute
class UHeroAttributeComponent;

// TimeEvent
class UTimeEventComponent;

// UI
class UWidgetComponent;




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

	UFUNCTION(NetMulticast, Reliable)
	void SetCamera(FVector NewCameraLocation, FRotator NewCameraRotation, float NewArmLength, FVector NewSocketOffset);


	void StartGameCamera(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	UHeroAttributeComponent* GetHeroAttributeComponent()
	{
		return HeroAttributeComponent;
	}

	UFUNCTION(BlueprintCallable)
	UWidgetComponent* GetWidgetComponent()
	{
		return WidgetComponent;
	}	

	UInputMappingContext* GetInputMappingContext()
	{
		return InputMappingContext;
	}

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Look(const FInputActionValue& Value);
	virtual void Move(const FInputActionValue& Value);

	virtual void Attack(const FInputActionValue& Value) {}
	virtual void SkillQ(const FInputActionValue& Value) {}
	virtual void SkillE(const FInputActionValue& Value) {}
	virtual void SkillR(const FInputActionValue& Value) {}

	virtual void MouseWheel(const FInputActionValue& Value);
	virtual void UIModeOn(const FInputActionValue& Value);
	virtual void UIModeOff(const FInputActionValue& Value);

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
	UTimeEventComponent* TimeEventComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggTimeEvent")
	UWidgetComponent* WidgetComponent;


	

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bAimMode = false;
	bool bIsUIMode = false;

protected:
	bool bIsCameraTransitioning = false;
	float TransitionAlpha = 0.0f;
	float TransitionSpeed = 1.0f; // 카메라 회전 속도

	FVector StartCameraLocation;
	FRotator StartCameraRotation;
	float StartArmLength;
	FVector StartSocketOffset;

	FVector TargetCameraLocation;
	FRotator TargetCameraRotation;
	float TargetArmLength;
	FVector TargetSocketOffset;



	int MaxAttackIndex;
	int CurAttackIndex;
};
