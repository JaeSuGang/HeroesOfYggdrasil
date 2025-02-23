// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TestAnimInstance_kjh.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UTestAnimInstance_kjh : public UAnimInstance
{
	GENERATED_BODY()

public:
	void SetIsAttacking(bool _Value)
	{
		bIsAttacking = _Value;
	}


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking = false;
};
