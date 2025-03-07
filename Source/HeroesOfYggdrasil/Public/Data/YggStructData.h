// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YggStructData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FPlayerSkillInfoRow : public FTableRowBase
{
	GENERATED_BODY()
	FPlayerSkillInfoRow() {}
	~FPlayerSkillInfoRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CoolTime =0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ContinueTime = 0.0f;
};


USTRUCT(BlueprintType)
struct FPlayerBaseStatusInfoRow : public FTableRowBase
{
	GENERATED_BODY()
	FPlayerBaseStatusInfoRow() {}
	~FPlayerBaseStatusInfoRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Hp = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float SpeedRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float JumpRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int MaxAttackIndex = 0;
};







UCLASS()
class HEROESOFYGGDRASIL_API UYggStructData : public UObject
{
	GENERATED_BODY()

};
