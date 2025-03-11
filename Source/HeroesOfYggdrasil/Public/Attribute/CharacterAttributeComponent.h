// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/AttributeComponent.h"
#include "CharacterAttributeComponent.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UCharacterAttributeComponent : public UAttributeComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
	float Hp;
	
};
