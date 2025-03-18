// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Data/YggStructData.h"
#include "HeroAttributeComponent.generated.h"

/**
 *	김성훈
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
	int GetCurComboAttack() const
	{
		return CurComboAttack;
	}

	int GetMaxComboAttack() const
	{
		return MaxComboAttack;
	}

	void SetCombo(int num)
	{
		CurComboAttack = 0;
		MaxComboAttack = num;
	}

public:
	UPROPERTY(EditAnywhere)
	UDataTable* Data;

	UPROPERTY(BlueprintReadOnly)
	float SpeedRate = 1.0f;
	UPROPERTY(BlueprintReadOnly)
	float JumpRate = 1.0f;

	void SaveComboAttack();
	void ResetComboAttack();

	//UPROPERTY(Server, Reliable)
	//void Server_SaveComboAttack();
	//UPROPERTY(Server, Reliable)
	//void Server_ResetComboAttack();

	UFUNCTION()
	void OnRep_Combo();
	
	UPROPERTY()
	FOnComboChanged ServerDelegate_OnComboChanged;
	UPROPERTY()
	FOnComboChanged ClientDelegate_OnComboChanged;
	UPROPERTY()
	FOnComboChanged MulticastDelegate_OnComboChanged;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Combo, EditAnywhere)
	int CurComboAttack;

	UPROPERTY(Replicated, EditAnywhere)
	int MaxComboAttack;


};
