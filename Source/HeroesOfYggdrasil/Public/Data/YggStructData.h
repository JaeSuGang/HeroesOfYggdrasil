// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YggStructData.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FHeroSkillInfoRow : public FTableRowBase
{
	GENERATED_BODY()
	FHeroSkillInfoRow() {}
	~FHeroSkillInfoRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float CoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float ContinueTime;
};


USTRUCT(BlueprintType)
struct FHeroBaseStatusInfoRow : public FTableRowBase
{
	GENERATED_BODY()
	FHeroBaseStatusInfoRow() {}
	~FHeroBaseStatusInfoRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float Hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float GroundSpeedRate =1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float AttackSpeedRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float JumpRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	int MaxAttackIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FHeroSkillInfoRow SkillQInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FHeroSkillInfoRow SkillEInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FHeroSkillInfoRow SkillRInfo;
};







UCLASS()
class HEROESOFYGGDRASIL_API UYggStructData : public UObject
{
	GENERATED_BODY()

};
