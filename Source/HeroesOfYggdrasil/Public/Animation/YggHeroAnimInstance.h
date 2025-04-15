// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "YggHeroAnimInstance.generated.h"



/**	김성훈
 * 
 */


class AYggHero;
class UCharacterMovementComponent;
class UAnimMontage;
class UHeroAttributeComponent;

UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API UYggHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UYggHeroAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	void PlayMontage(FName MontageName,float PlayRate = 1.0f);
	void JumpMontage(FName MontageName, FName SectionName);
	void StopMontage();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayMontageEvent(UAnimMontage* Montage,float PlayRate);

protected:

public:
	void UpdateAimOffset();
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	TMap<FName, UAnimMontage*> MontageMap;

	UPROPERTY(BlueprintReadOnly)
	AYggHero* Hero;
	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly)
	UHeroAttributeComponent* HeroAttributeComponent;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly)
	float Direction;
	UPROPERTY(BlueprintReadOnly)
	float Roll;
	UPROPERTY(BlueprintReadOnly)
	float Pitch;
	UPROPERTY(BlueprintReadOnly)
	float Yaw;

	UPROPERTY(BlueprintReadWrite)
	bool bIsRoll = false;

	UPROPERTY(BlueprintReadWrite)
	float RoolSpeed = 1.0f;

private:
	
};
