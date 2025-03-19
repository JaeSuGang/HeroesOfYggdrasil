// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/AttributeComponent.h"
#include "CharacterAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamage, float, fAmount);

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API UCharacterAttributeComponent : public UAttributeComponent
{
	GENERATED_BODY()

public:

protected:
	void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_TakeDamage(float fAmount);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetHp(float fAmount);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetMaxHp(float fAmount);

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHp() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetMaxHp() const;



public:
	/* TakeDamage를 호출했을 때 같이 호출될 함수들을 이곳에 AddDynamic
	* Server, NetMulticast, Client 함수도 Bind 가능
	*/
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamage Delegate_OnTakeDamage;

protected:
	UPROPERTY(Replicated, EditAnywhere)
	float Hp;

	UPROPERTY(Replicated, EditAnywhere)
	float MaxHp;
};
