// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Data/YggStructData.h"
#include "HeroAttributeComponent.generated.h"

/**
 *	김성훈
 */
class UDataTable;
UCLASS()
class HEROESOFYGGDRASIL_API UHeroAttributeComponent : public UCharacterAttributeComponent
{
	GENERATED_BODY()

protected:

public:
	UPROPERTY(EditAnywhere)
	UDataTable* Data;

	FHeroBaseStatusInfoRow* Status;

	UPROPERTY(BlueprintReadOnly)
	float SpeedRate = 1.0f;
	UPROPERTY(BlueprintReadOnly)
	float JumpRate = 1.0f;
};
