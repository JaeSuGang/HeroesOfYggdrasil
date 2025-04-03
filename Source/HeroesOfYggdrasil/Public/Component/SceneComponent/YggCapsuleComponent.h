// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "YggCapsuleComponent.generated.h"

/**
 * 
 */


class AYggCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HEROESOFYGGDRASIL_API UYggCapsuleComponent : public UCapsuleComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void CollisionOn();
	UFUNCTION(BlueprintCallable)
	virtual void CollisionOff();

	UFUNCTION(BlueprintCallable)
	virtual void SetOwnerCharacter(AYggCharacter* Owner)
	{
		OwnerCharacter = Owner;
	}
	
protected:
	UPROPERTY()
	AYggCharacter* OwnerCharacter;

};
