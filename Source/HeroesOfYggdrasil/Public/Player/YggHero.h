// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggCharacter.h"

#include "YggHero.generated.h"

/**
 * 김성훈, 김지호
 * 히어로 기본 클래스
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkillCastEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillCast, float, Duration);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillQ, FName, SkillName, float, CoolTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillE, FName, SkillName, float, CoolTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillR, FName, SkillName, float, CoolTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRespawn, float, RespawnTime);

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
class UCharacterAttributeComponent;

// UI
class UWidgetComponent;
class AYggMiniMapIconActor;
class UNicknameBarComponent;

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

	virtual UCharacterAttributeComponent* GetAttributeComponent() override;


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

	bool IsAimMode() const { return bAimMode; }

	UFUNCTION(BlueprintCallable)
	UCaptureComponent* GetMiniMapCaptureComponent()
	{
		return MiniMapCaptureComponent;
	}

	AYggMiniMapIconActor* GetMiniMapIcon()
	{
		return MiniMapIcon;
	}

	UFUNCTION(NetMulticast, Reliable)
	void TakeDamageEffect(float Att);

	virtual void Attack(const FInputActionValue& Value);
	virtual void Jump() override;

	UFUNCTION()
	void Respawn();

	UFUNCTION()
	void HandleMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	int GetDeathCount() const { return DeathCount; }

protected:
	virtual void OnRep_Controller() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	virtual void Look(const FInputActionValue& Value);
	virtual void Move(const FInputActionValue& Value);

	virtual void Roll(const FInputActionValue& Value);
	UFUNCTION(Server, Reliable)
	void ServerRoll(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRoll(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ServerAttack(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastAttack(const FInputActionValue& Value);

	virtual void EndAttack(const FInputActionValue& Value);

	UFUNCTION()
	virtual void SkillQ(const FInputActionValue& Value);
	UFUNCTION(Server, Reliable)
	void ServerHeroSkillQ(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastHeroSkillQ(const FInputActionValue& Value);

	UFUNCTION()
	virtual void SkillE(const FInputActionValue& Value);
	UFUNCTION(Server, Reliable)
	void ServerHeroSkillE(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastHeroSkillE(const FInputActionValue& Value);

	UFUNCTION()
	virtual void SkillR(const FInputActionValue& Value);
	UFUNCTION(Server, Reliable)
	void ServerHeroSkillR(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastHeroSkillR(const FInputActionValue& Value);

	UFUNCTION()
	void Die(float Delegate);
	UFUNCTION(Server, Reliable)
	void ServerDie(float Delegate);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastDie(float Delegate);

	virtual void ToggleAimMode();
	virtual void SetAimMode(bool Value);

	void UpdateStatus();

	virtual FName GetHeroName() const { return FName(TEXT("Hero")); };

	/*UFUNCTION(Server, Reliable)
	void ServerDie(float Delegate);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastDie();*/

	virtual void CameraZoomInOut(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggCamera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggCamera")
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category = "YggInput")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "YggInput")
	TArray<UInputMappingContext*> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "YggInput")
	TMap<FName, UInputAction*> ActionMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggAnimation")
	UYggHeroAnimInstance* HeroAnimInstance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UHeroAttributeComponent* HeroAttributeComponent;



	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NickName")
	//UWidgetComponent* NickNameWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggCamera")
	UCaptureComponent* FaceCaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YggCamera")
	UCaptureComponent* MiniMapCaptureComponent;

	UPROPERTY(EditDefaultsOnly, Category = "YggMiniMapIcon")
	TSubclassOf<AYggMiniMapIconActor> MiniMapIconClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NickName")
	UNicknameBarComponent* NickNameWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bAimMode = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bIsUIMode = false;


	UPROPERTY(Replicated)
	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName LeftSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName RightSocketName;

	UPROPERTY()
	AYggMiniMapIconActor* MiniMapIcon;

public:

	UFUNCTION(Server, Reliable)
	void Server_SetAimDirection(const FVector& InAimDir);

	UFUNCTION()
	FVector Local_GetAimDirection(FName SocketName);

	UFUNCTION()
	FVector GetAimDirection() const { return AimDirection; }


	UPROPERTY(BlueprintAssignable, Category = "Widget")
	FOnSkillCast OnSkillCast;

	UPROPERTY(BlueprintAssignable, Category = "Widget")
	FOnSkillCastEnd OnSkillCastEnd;

	UPROPERTY(BlueprintAssignable, Category = "Widget Skill")
	FOnSkillQ OnSkillQ;
	UPROPERTY(BlueprintAssignable, Category = "Widget Skill")
	FOnSkillE OnSkillE;
	UPROPERTY(BlueprintAssignable, Category = "Widget Skill")
	FOnSkillR OnSkillR;

	UPROPERTY(BlueprintAssignable, Category = "Widget Respawn")
	FOnRespawn OnRespawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggHero")
	float RespawnTime = 15.0f;


	FTransform StartTransform;

	FVector GetTargetLocation() const { return TargetLocation; }

	int32 GetDeathCount() const { return DeathCount; }
protected:
	UPROPERTY(Replicated)
	int32 DeathCount = 0;

	UPROPERTY(Replicated)
	FVector TargetLocation;


public:
	void ApplyStun();
	void ClearStun();
};
