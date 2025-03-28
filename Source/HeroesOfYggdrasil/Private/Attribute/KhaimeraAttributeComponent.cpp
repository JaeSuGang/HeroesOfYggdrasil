// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/KhaimeraAttributeComponent.h"

void UKhaimeraAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = true;
}

void UKhaimeraAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


