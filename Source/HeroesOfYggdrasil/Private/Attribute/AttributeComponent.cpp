
#include "Attribute/AttributeComponent.h"

#include "Net/UnrealNetwork.h"

UAttributeComponent::UAttributeComponent()
{
	SetIsReplicatedByDefault(true);

	PrimaryComponentTick.bCanEverTick = false;


}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UAttributeComponent, GameplayTags);
}

bool UAttributeComponent::HasTag(const FName& Tag)
{
	return GameplayTags.HasTag(FGameplayTag::RequestGameplayTag(Tag));
}

bool UAttributeComponent::HasTagExact(const FName& Tag)
{
	return GameplayTags.HasTagExact(FGameplayTag::RequestGameplayTag(Tag));
}

void UAttributeComponent::OnRep_Tags()
{

}

void UAttributeComponent::AddTag_Implementation(const FName& Tag)
{
	GameplayTags.AddTag(FGameplayTag::RequestGameplayTag(Tag));
}

void UAttributeComponent::AddTags_Implementation(const TArray<FName>& Tags)
{
	for (const FName Tag : Tags)
	{
		GameplayTags.AddTag(FGameplayTag::RequestGameplayTag(Tag));
	}
}

void UAttributeComponent::RemoveTag_Implementation(const FName& Tag)
{
	GameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag(Tag));
}

void UAttributeComponent::RemoveTags_Implementation(const TArray<FName>& Tags)
{
	for (const FName Tag : Tags)
	{
		GameplayTags.RemoveTag(FGameplayTag::RequestGameplayTag(Tag));
	}
}

