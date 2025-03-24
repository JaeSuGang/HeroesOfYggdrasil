// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/HeroAttributeComponent.h"
#include "Engine/DataTable.h"
#include "Net/UnrealNetwork.h"

void UHeroAttributeComponent::BeginPlay()
{
    Super::BeginPlay();   
}

void UHeroAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool UHeroAttributeComponent::IsAttackCheck()
{
	return HasTagExact(TEXT("Character.State.NotAttackable"));
}
