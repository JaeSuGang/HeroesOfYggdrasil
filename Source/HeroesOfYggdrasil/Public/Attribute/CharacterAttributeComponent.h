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

protected:
	/* Do Not Use */
	UFUNCTION(Client, Reliable)
	void Client_TakeDamage(float fAmount);

public:
	/* 
	* 모든 클라이언트에서 실행되어야 하는 함수는
	* 서버측에서 UPROPERTY(NetMulticast) 함수를 이곳에 AddDynamic시켜야 함
	* 클라이언트측에서 Bind 시킨 함수는 다른 클라이언트들이 모르기 때문임
	*/
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamage ServerDelegate_OnTakeDamage;

	/*
	* 만일 클라이언트측에서 자신만이 호출할 함수를 AddDynamic하는 상황이라면
	* 이 델리게이트를 써도 됨.
	*/
	UPROPERTY(BlueprintAssignable)
	FOnTakeDamage ClientDelegate_OnTakeDamage;

protected:
	UPROPERTY(Replicated, EditAnywhere)
	float Hp;

	UPROPERTY(Replicated, EditAnywhere)
	float MaxHp;
};
