// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YggEnumData.generated.h"

/**
 * 
 */






UCLASS()
class HEROESOFYGGDRASIL_API UYggEnumData : public UObject
{
	GENERATED_BODY()
	
};



UENUM(BlueprintType)
enum class EEnemyAIState : uint8
{
	Idle UMETA(DisplayName = "대기"),
	Attack UMETA(DisplayName = "공격"),
	Await UMETA(DisplayName = "공격대기"),
	ApproachToAttack UMETA(DisplayName = "접근"),
	Strafe UMETA(DisplayName = "와리가리"),
	Trace UMETA(DisplayName = "추적"),
	TraceBack UMETA(DisplayName = "복귀"),
	TraceYggdrasil UMETA(DisplayName = "이그드라실공격"),
	DragonBreath UMETA(DisplayName = "드래곤브레스"),
	DragonMeteor UMETA(DisplayName = "드래곤메테오"),
	Hit UMETA(DisplayName = "피격"),
	Death UMETA(DisplayName = "죽음"),
	DeathFallen UMETA(DisplayName = "다운"),
	MAX UMETA(DisplayName = "MAX"),
};

UENUM(BlueprintType)
enum class EStatusEffectType : uint8
{
	Poison    UMETA(DisplayName = "Poison"),
	Burn      UMETA(DisplayName = "Burn"),
	Slow	  UMETA(DisplayName = "Slow"),
	Stunned   UMETA(DisplayName = "Stunned"),
	MAX UMETA(DisplayName = "MAX")
};


UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Unknown			UMETA(DisplayName = "Unknown"),
	Minion_Melee	UMETA(DisplayName = "Minion_Melee"),
	Minion_Archer	UMETA(DisplayName = "Minion_Archer"),
	Minion_Witch	UMETA(DisplayName = "Minion_Witch"),
	Dragon			UMETA(DisplayName = "Dragon"),
	MAX UMETA(DisplayName = "MAX")
};
