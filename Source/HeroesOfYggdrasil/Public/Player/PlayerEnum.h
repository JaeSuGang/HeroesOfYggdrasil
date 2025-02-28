// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerEnum.generated.h"

/**
 *	김성훈
 */



UENUM(BlueprintType)
enum class UGait :uint8
{
	Standing	UMETA(DisplayName = "Standing"),
	Walking     UMETA(DisplayName = "Walking"),
	Running     UMETA(DisplayName = "Running"),
	Sprinting   UMETA(DisplayName = "Sprinting"),
	Crouching   UMETA(DisplayName = "Crouching")
};





UCLASS()
class HEROESOFYGGDRASIL_API UPlayerEnum : public UObject
{
	GENERATED_BODY()
	
};
