// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YggEnumData.h"
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
	float CurHp = 100.0f; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float MaxHp = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float HpRegen = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float GroundSpeedRate =1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float AttackSpeedRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float JumpRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	int CurAttackIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	int MaxAttackIndex = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float AttPower = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float DefPower = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float CriticalChance = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float CriticalDamage = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FHeroSkillInfoRow SkillQInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FHeroSkillInfoRow SkillEInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FHeroSkillInfoRow SkillRInfo;
};




USTRUCT(BlueprintType)
struct FAIData
{
	GENERATED_BODY()
	FAIData() {}
	~FAIData() {}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double TraceRange = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FName TargetGroupName = TEXT("None");
};


USTRUCT(BlueprintType)
struct FPlayAIData
{
	GENERATED_BODY()

	FPlayAIData() {}
	~FPlayAIData() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FAIData Data;

	EEnemyAIState EnemyAIState = EEnemyAIState::Idle;
	double CurHP = 100;
	class APawn* SelfPawn = nullptr;
	AActor* TargetActor = nullptr;
	class AEnemyAnimCharacter* SelfAnimPawn = nullptr;
	class UEnemyBaseAnimInstance* UEnemyBaseAnimInstance = nullptr;
	FVector OriginPos;

};

UCLASS(BlueprintType)
class UAIDataObject : public UObject
{
	GENERATED_BODY()

	UAIDataObject() {}
	~UAIDataObject() {}

public:
	FPlayAIData PlayData;
};


USTRUCT(BlueprintType)
struct FMonsterDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FMonsterDataRow() {}
	~FMonsterDataRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FAIData AIData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	class UBehaviorTree* BTAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	class USkeletalMesh* Mesh;
};

UCLASS(BlueprintType)
class UEnemyConst : public UObject
{
	GENERATED_BODY()

public:
	class AI
	{
	public:
		static FName EnemyAIDataName;
	};
};






UCLASS()
class HEROESOFYGGDRASIL_API UYggStructData : public UObject
{
	GENERATED_BODY()

};
