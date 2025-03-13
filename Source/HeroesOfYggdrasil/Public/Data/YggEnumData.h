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
	Strafe UMETA(DisplayName = "와리가리"),
	Trace UMETA(DisplayName = "추적"),
	TraceBack UMETA(DisplayName = "복귀"),
	Hit UMETA(DisplayName = "피격"),
	Death UMETA(DisplayName = "죽음"),
	DeathFallen UMETA(DisplayName = "다운"),
	MAX UMETA(DisplayName = "MAX"),
};
