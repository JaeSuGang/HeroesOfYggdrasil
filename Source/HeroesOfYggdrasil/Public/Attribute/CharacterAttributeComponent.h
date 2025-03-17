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
	/* 체력이 변했을 때 서버 컴퓨터만 실행되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged ServerDelegate_OnHealthChanged;

	/* 체력이 변했을 때 캐릭터의 소유자만 실행되는 델리게이트 */
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged ClientDelegate_OnHealthChanged;

	/* 체력이 변했을 때 모두가 실행되는 델리게이트*/
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged MulticastDelegate_OnHealthChanged;

public:
	UFUNCTION()
	void Foo();


	UFUNCTION()
	void OnRep_Hp();

protected:
	UPROPERTY(ReplicatedUsing=OnRep_Hp, EditAnywhere)
	float Hp;

	UPROPERTY(Replicated, EditAnywhere)
	float MaxHp;
};
