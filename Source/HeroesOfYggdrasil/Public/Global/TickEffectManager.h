// TickEffectManager.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/YggEnumData.h"
#include "TickEffectManager.generated.h"

class AYggTickActor;
class AYggCharacter;

UCLASS()
class HEROESOFYGGDRASIL_API UTickEffectManager : public UObject
{
	GENERATED_BODY()

public:
	/** 상태이상 TickActor 생성 (중복 방지 포함) */
	UFUNCTION(BlueprintCallable, Category = "TickEffect")
	static AYggTickActor* SpawnTickActorIfNeeded(
		AYggCharacter* Owner,
		AYggCharacter* Target,
		EStatusEffectType EffectType,
		float TickTime,
		float Scale = 1.0f
	);


};
