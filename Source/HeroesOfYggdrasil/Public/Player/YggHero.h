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
class USceneCaptureComponent2D;

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

// TimeEvent
class UTimeEventComponent;

// UI
class UWidgetComponent;

struct FHeroCameraData;




UCLASS()
class HEROESOFYGGDRASIL_API AYggHero : public AYggCharacter
{
	GENERATED_BODY()
public:
	AYggHero();

	UFUNCTION(NetMulticast, Reliable)
	void SetCamera(FVector NewCameraLocation, FRotator NewCameraRotation, float NewArmLength, FVector NewSocketOffset);
	void StartGameCamera(float DeltaTime);

	//void CameraMove(FCameraMoveData* CameraMoveData);

	UFUNCTION(BlueprintCallable)
	UHeroAttributeComponent* GetHeroAttributeComponent()
	{
		return HeroAttributeComponent;
	}

	UFUNCTION(BlueprintCallable)
	UInputMappingContext* GetInputMappingContext()
	{
		return InputMappingContext;
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

	virtual void Attack(const FInputActionValue& Value) {}
	virtual void SkillQ(const FInputActionValue& Value) {}
	virtual void SkillE(const FInputActionValue& Value) {}
	virtual void SkillR(const FInputActionValue& Value) {}

	virtual void ToggleAimMode();
	virtual void SetAimMode(bool Value);

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
	UTimeEventComponent* TimeEventComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggTimeEvent")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "YggCamera")
	USceneCaptureComponent2D* SceneCaptureComponent2D;
	

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bAimMode = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
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

	FVector GetAimWorldLocation(APlayerController* PlayerController);
	void AimRaycast(APlayerController* PlayerController);


	int MaxAttackIndex;
	int CurAttackIndex;
};
