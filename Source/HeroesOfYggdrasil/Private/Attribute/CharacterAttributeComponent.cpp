// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/CharacterAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


void UCharacterAttributeComponent::Server_TakeDamage_Implementation(float fAmount)
{
	HP -= fAmount;

	ServerDelegate_OnTakeDamage.Broadcast(fAmount);
	Client_TakeDamage(fAmount);
}

void UCharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCharacterAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterAttributeComponent, HP);
	DOREPLIFETIME(UCharacterAttributeComponent, MaxHP);
}

void UCharacterAttributeComponent::Server_SetMaxHP_Implementation(float fAmount)
{
	MaxHP = fAmount;
}

void UCharacterAttributeComponent::Server_SetHP_Implementation(float fAmount)
{
	HP = fAmount;
}

void UCharacterAttributeComponent::Client_TakeDamage_Implementation(float fAmount)
{
	ClientDelegate_OnTakeDamage.Broadcast(fAmount);
}


