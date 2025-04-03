// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Data/YggStructData.h"
#include "HeroAttributeComponent.generated.h"

/**
 *	
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboChanged);

class UDataTable;
UCLASS()
class HEROESOFYGGDRASIL_API UHeroAttributeComponent : public UCharacterAttributeComponent
{
	GENERATED_BODY()

public:
	UHeroAttributeComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void ServerSetBaseData(const FName& Name);

public:
	UPROPERTY(EditAnywhere)
	UDataTable* BaseData;


	bool IsAttackCheck();
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float HPRegen;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float JumpPower;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float CriticalChance;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float CriticalDamageRate;
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillQCurCoolTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillECurCoolTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillRCurCoolTime;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillQMaxCoolTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillEMaxCoolTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillRMaxCoolTime;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillQCurContinueTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillECurContinueTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillRCurContinueTime;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillQMaxContinueTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillEMaxContinueTime;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillRMaxContinueTime;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	FHeroSkillInfoRow SkillQInfo;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	FHeroSkillInfoRow SkillEInfo;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	FHeroSkillInfoRow SkillRInfo;

	// 수정 필요.
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	int CurRollCount = 3;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	int MaxRollCount = 3;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float RollCurCoolTime = 0.0f;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float RollMaxCoolTime = 5.0f;
};
