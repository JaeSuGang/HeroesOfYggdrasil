// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/HeroAttributeComponent.h"
#include "KhaimeraAttributeComponent.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UKhaimeraAttributeComponent : public UHeroAttributeComponent
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
};
