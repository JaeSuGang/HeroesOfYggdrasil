// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YggEnumData.h"
#include "Attribute/EnemyAttributeComponent.h"
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
struct FHeroCameraData : public FTableRowBase
{
	GENERATED_BODY()
	FHeroCameraData() {}
	~FHeroCameraData() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float ArmLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FRotator CameraRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FVector SocketOffset;
	
};



USTRUCT(BlueprintType)
struct FHeroBaseStatusInfoRow : public FTableRowBase
{
	GENERATED_BODY()
	FHeroBaseStatusInfoRow() {}
	~FHeroBaseStatusInfoRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float CurHP = 100.0f; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float MaxHP = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float HPRegen = 1.0f;
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
	FName EnemyName = FName("");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double TraceRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double StrafeRange = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double StrafeSpeed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double StrafeTime= 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double AttackRange = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double ApproachSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double YggAttackRange = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double AttackTime = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double AwaitTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double StandardZeroTime= 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double TraceBackSpeed = 1200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double TraceSpeed = 600.0f;
};


USTRUCT(BlueprintType)
struct FPlayAIData
{
	GENERATED_BODY()

	FPlayAIData() {}
	~FPlayAIData() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FAIData Data;

	EEnemyAIState EnemyAIState = EEnemyAIState::TraceYggdrasil;

	double CurHP = 100;

	class APawn* SelfPawn = nullptr;

	AActor* TargetActor = nullptr;

	class AEnemyAnimCharacter* SelfAnimPawn = nullptr;

	class UEnemyBaseAnimInstance* UEnemyBaseAnimInstance = nullptr;

	FVector OriginPos;

	
	
	// int AttackAnimationCount;

	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TMap<EEnemyAIState, UAnimMontage*> Animations;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TArray<UAnimMontage*> AttackAnimations;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSubclassOf<UAnimInstance> AnimationBluePrint;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSubclassOf<class AEnemyCharacter> SpawnClass;
};




USTRUCT(BlueprintType)
struct FDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	FDataTableRow() {}
	~FDataTableRow() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	UDataTable* Resources;
};


/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UGlobalDataTable : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static TSubclassOf<class AEnemyCharacter> GetEnemySpawnClass(UWorld* _World, const FString& _Name);
	static const FMonsterDataRow GetMonsterData(UWorld* _World, const FString& _Name);


};




UCLASS()
class HEROESOFYGGDRASIL_API UYggStructData : public UObject
{
	GENERATED_BODY()

};
