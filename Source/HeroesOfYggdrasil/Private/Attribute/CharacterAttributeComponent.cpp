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

void UCharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	ClientDelegate_OnHealthChanged.AddDynamic(this, &UCharacterAttributeComponent::Foo);
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
	if (GetWorld()->GetAuthGameMode())
	{
		OnRep_Hp();
	}
}

float UCharacterAttributeComponent::GetHp() const
{
	return Hp;
}

float UCharacterAttributeComponent::GetMaxHp() const
{
	return MaxHp;
}

void UCharacterAttributeComponent::Foo()
{

}

void UCharacterAttributeComponent::OnRep_Hp()
{
	if (GetOwner()->HasAuthority())
		ServerDelegate_OnHealthChanged.Broadcast();

	if (GetOwner()->HasLocalNetOwner())
		ClientDelegate_OnHealthChanged.Broadcast();

	MulticastDelegate_OnHealthChanged.Broadcast();
}
