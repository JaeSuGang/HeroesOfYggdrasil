// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TickUtilityFunctionLibrary.generated.h"


class AYggHero;
class AYggTickActor;


/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UTickUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Tick")
	static AYggTickActor* FindAttachedTickActor(AYggHero* HeroTarget);
};