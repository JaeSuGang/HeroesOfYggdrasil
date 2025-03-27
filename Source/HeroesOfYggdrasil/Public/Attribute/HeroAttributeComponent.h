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

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere)
	UDataTable* Data;

	//UPROPERTY(BlueprintReadOnly)
	//float SpeedRate = 1.0f;
	//UPROPERTY(BlueprintReadOnly)
	//float JumpRate = 1.0f;

	bool IsAttackCheck();
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float HPRegen;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SpeedRate;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float JumpRate;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float AttackSpeedRate;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float CriticalChance;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float CriticalDamageRate;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillQCoolTime;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillECoolTime;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly)
	float SkillRCoolTime;
};
