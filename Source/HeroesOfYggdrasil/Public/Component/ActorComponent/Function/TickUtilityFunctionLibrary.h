// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/YggEnumData.h"
#include "TickUtilityFunctionLibrary.generated.h"


class AYggHero;
class AEnemyCharacter;
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
	static AYggTickActor* FindAttachedTickActor(AYggCharacter* HeroTarget);

	static EStatusEffectType FindStatusEffectType(AEnemyCharacter* Enemy);

	static FName ConvertStatusEffectTypeToName(EStatusEffectType Type);
	
};