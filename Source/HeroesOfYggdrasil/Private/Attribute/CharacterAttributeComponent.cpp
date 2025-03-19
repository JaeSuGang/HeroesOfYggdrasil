// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/CharacterAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


void UCharacterAttributeComponent::Server_TakeDamage_Implementation(float fAmount)
{
	Hp -= fAmount;

	Delegate_OnTakeDamage.Broadcast(fAmount);
}

void UCharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCharacterAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterAttributeComponent, Hp);
	DOREPLIFETIME(UCharacterAttributeComponent, MaxHp);
}

void UCharacterAttributeComponent::Server_SetMaxHp_Implementation(float fAmount)
{
	MaxHp = fAmount;
}

void UCharacterAttributeComponent::Server_SetHp_Implementation(float fAmount)
{
	Hp = fAmount;
}

float UCharacterAttributeComponent::GetHp() const
{
	return Hp;
}

float UCharacterAttributeComponent::GetMaxHp() const
{
	return MaxHp;
}

