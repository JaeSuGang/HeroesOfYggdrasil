// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/CharacterAttributeComponent.h"
#include "GameFramework/Character.h"


void UCharacterAttributeComponent::Server_TakeDamage_Implementation(float fAmount)
{
	Hp -= fAmount;
	Client_OnTakeDamage(fAmount);
}

void UCharacterAttributeComponent::Client_OnTakeDamage_Implementation(float fAmount)
{
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		if (Character->HasLocalNetOwner())
		{
			Delegate_OnTakeDamage.Broadcast(fAmount);
		}
	}
}

