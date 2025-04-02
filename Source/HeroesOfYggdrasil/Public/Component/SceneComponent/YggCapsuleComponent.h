// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "YggCapsuleComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HEROESOFYGGDRASIL_API UYggCapsuleComponent : public UCapsuleComponent
{
	GENERATED_BODY()
public:
	

	
	UFUNCTION(BlueprintCallable)
	void CollisionOn();
	UFUNCTION(BlueprintCallable)
	void CollisionOff();
};
