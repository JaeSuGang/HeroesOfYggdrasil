// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/CharacterAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


void UCharacterAttributeComponent::Server_TakeDamage_Implementation(float fAmount)
{
	Hp -= fAmount;
	if (GetWorld()->GetAuthGameMode())
	{
		OnRep_Hp();
	}
}

void UCharacterAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterAttributeComponent, Hp);
	DOREPLIFETIME(UCharacterAttributeComponent, MaxHp);
}

void UCharacterAttributeComponent::OnRep_Hp()
{
	if (GetOwner()->HasLocalNetOwner())
	{
		ClientDelegate_OnHealthChanged.Broadcast();
	}
}
