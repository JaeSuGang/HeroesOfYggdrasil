// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/AttributeComponent.h"
#include "CharacterAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamage, float, NewHealth);

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API UCharacterAttributeComponent : public UAttributeComponent
{
	GENERATED_BODY()

public:

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_TakeDamage(float fAmount);

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_OnTakeDamage(float fAmount);
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamage Delegate_OnTakeDamage;

protected:
	UPROPERTY(EditAnywhere)
	float Hp;

	
};
