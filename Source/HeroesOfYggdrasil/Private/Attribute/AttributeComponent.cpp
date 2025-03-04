// Fill out your copyright notice in the Description page of Project Settings.


#include "Attribute/AttributeComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UAttributeComponent, Status);
}

bool UAttributeComponent::HasStatusTag(const FName& Tag)
{
	return Status.HasTag(FGameplayTag::RequestGameplayTag(Tag));
}

void UAttributeComponent::AddStatusTag(const FName& Tag)
{
	
	Status.AddTag(FGameplayTag::RequestGameplayTag(Tag));
}

void UAttributeComponent::AddStatusTags(const TArray<FName>& Tags)
{
	for (const FName Tag : Tags)
	{
		Status.AddTag(FGameplayTag::RequestGameplayTag(Tag));
	}
}

void UAttributeComponent::RemoveStatusTag(const FName& Tag)
{
	Status.RemoveTag(FGameplayTag::RequestGameplayTag(Tag));
}

void UAttributeComponent::RemoveStatusTags(const TArray<FName>& Tags)
{
	for (const FName Tag : Tags)
	{
		Status.RemoveTag(FGameplayTag::RequestGameplayTag(Tag));
	}
}

