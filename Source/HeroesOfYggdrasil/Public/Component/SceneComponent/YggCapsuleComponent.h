// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "YggCapsuleComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverLapBeginPlusLogic);

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
	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnOverLapBeginPlusLogic PlusLogic;
protected:

	

	UPROPERTY()
	AYggCharacter* OwnerCharacter;

};
