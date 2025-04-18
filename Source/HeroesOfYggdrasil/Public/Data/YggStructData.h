// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YggEnumData.h"
#include "Attribute/EnemyAttributeComponent.h"
#include "NiagaraSystem.h"
#include "YggStructData.generated.h"

/**
 *
 */




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
struct FHeroSkillInfoRow : public FTableRowBase
{
	GENERATED_BODY()
	FHeroSkillInfoRow() {}
	~FHeroSkillInfoRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float SkillCoefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float CoolTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float ContinueTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float CastingTime;
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
	float MaxMoveSpeed =1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float AttackSpeedRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float JumpRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float AttPower = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float DefPower = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float CriticalChance = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float CriticalDamageRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FHeroSkillInfoRow AttackInfo;

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
	FVector Scale = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double MaxHP = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double EnemyAttackPoints = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double EnemyDefensePoints = 0;

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
	double RangeAttackTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double AwaitTime = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double TickAttackTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double TargetCheckTime = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double DeathCheckTime = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double StandardZeroTime= 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double TraceBackSpeed = 1200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double TraceSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FName HeroDeathTagName = "Character.State.Death";

};

USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_BODY()
	FProjectileData() {}
	~FProjectileData() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double InitialSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double MaxSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	double InitialLocationFloat = 100.0f;
};

USTRUCT(BlueprintType)
struct FStatusEffectData
{
	GENERATED_BODY()
	FStatusEffectData() {}
	~FStatusEffectData() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* PoisonNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* StunNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* FrozenNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* BurnNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* PoisonParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* StunParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* FrozenParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* BurnParticleSystem;
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

	bool bUsedBreathAttack;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSubclassOf<UAnimInstance> AnimationBluePrint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSubclassOf<class AEnemyCharacter> SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSoftObjectPtr<UParticleSystem> TickParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSoftObjectPtr<UNiagaraSystem> TickNiagaraSystem;
};


USTRUCT(BlueprintType)
struct FProjectileDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FProjectileDataRow() {}
	~FProjectileDataRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FProjectileData ProjectileData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSoftObjectPtr<UStaticMesh> StaticMesh;
};


USTRUCT(BlueprintType)
struct FStatusTickDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FStatusTickDataRow() {}
	~FStatusTickDataRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float TickTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float Interval = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float DamageAmount = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSoftObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	TSoftObjectPtr<UNiagaraSystem> NiagaraSystem;
};

USTRUCT(BlueprintType)
struct FWarningAreaDataRow : public FTableRowBase
{
	GENERATED_BODY()

	FWarningAreaDataRow() {}
	~FWarningAreaDataRow() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	UStaticMesh* PlaneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	UMaterialInterface* WarningMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	UParticleSystem* RangeEffectParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	UNiagaraSystem* NiagaraEffectSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float TimeElapsed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	float EffectScaleFloat = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggData")
	FVector ScaleVector = FVector(2.0f, 2.0f, 1.0f);

	
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

USTRUCT(BlueprintType)
struct FSkillIcon : public FTableRowBase
{
	GENERATED_BODY()

	FSkillIcon() {}
	~FSkillIcon() {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SkillQIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SkillEIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SkillRIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SkillShifteIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* SkillBackGroundIcon;
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
