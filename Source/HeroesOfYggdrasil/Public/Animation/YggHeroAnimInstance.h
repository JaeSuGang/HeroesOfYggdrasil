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

UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API UYggHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	AYggHero* Hero;
	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly)
	float Direction;




private:
	
};
