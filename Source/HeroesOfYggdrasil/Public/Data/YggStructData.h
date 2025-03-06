// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YggStructData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FPlayerSkillInfoaRow : public FTableRowBase
{
	GENERATED_BODY()
	FPlayerSkillInfoaRow() {}
	~FPlayerSkillInfoaRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CoolTime =0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ContinueTime = 0.0f;
};






UCLASS()
class HEROESOFYGGDRASIL_API UYggStructData : public UObject
{
	GENERATED_BODY()

};
