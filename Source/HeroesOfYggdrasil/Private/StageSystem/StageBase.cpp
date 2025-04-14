// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/StageBase.h"

#include "Net/UnrealNetwork.h"

UStageBase::UStageBase()
{
	
}

bool UStageBase::IsSupportedForNetworking() const
{
	return true;
}

void UStageBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void UStageBase::BeginPlay(UStageSystem* NewStageSystem)
{
	StageSystem = NewStageSystem;
}

