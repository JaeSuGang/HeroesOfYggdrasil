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

UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API UYggHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	void PlayMontage(FName MontageName);
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PlayMontageEvent(UAnimMontage* Montage);
protected:
	void UpdateAimOffset();

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	TMap<FName, UAnimMontage*> MontageMap;



	UPROPERTY(BlueprintReadOnly)
	AYggHero* Hero;
	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* CharacterMovementComponent;

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

private:
	
};
