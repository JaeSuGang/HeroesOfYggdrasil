// Coded By AssortRock Unreal Engine Class Project

#include "CustomSystem/CustomSystem.h"

#include "Net/UnrealNetwork.h"

UCustomSystem::UCustomSystem()
{
	bReplicateUsingRegisteredSubObjectList = true;
	SetIsReplicatedByDefault(true);
}


void UCustomSystem::BeginPlay()
{
	Super::BeginPlay();

	RegisterObjectsToReplicate();
}

void UCustomSystem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnregisterObjectsToReplicate();
}

void UCustomSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void UCustomSystem::RegisterObjectsToReplicate()
{
}

void UCustomSystem::UnregisterObjectsToReplicate()
{
}

