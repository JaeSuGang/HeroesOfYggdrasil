// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"

#include "EnemyBaseAnimInstance.generated.h"

/**
 * 담당 : 장시혁
 */


class AEnemyCharacter;
class UCharacterMovementComponent;


UCLASS()
class HEROESOFYGGDRASIL_API UEnemyBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

protected:
	UPROPERTY(BlueprintReadOnly)
	AEnemyCharacter* Enemy;

	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly)
	float LocomotionDirection;


	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool OwnerHaveTag(FGameplayTag _TagToCheck) const;
};
