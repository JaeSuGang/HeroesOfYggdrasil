// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/AttributeComponent.h"
#include "CharacterAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API UCharacterAttributeComponent : public UAttributeComponent
{
	GENERATED_BODY()

public:

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_TakeDamage(float fAmount);

public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged ClientDelegate_OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged MulticastDelegate_OnHealthChanged;

public:
	UFUNCTION()
	void OnRep_Hp();

protected:
	UPROPERTY(ReplicatedUsing=OnRep_Hp, EditAnywhere)
	float Hp;

	UPROPERTY(Replicated, EditAnywhere)
	float MaxHp;
};
