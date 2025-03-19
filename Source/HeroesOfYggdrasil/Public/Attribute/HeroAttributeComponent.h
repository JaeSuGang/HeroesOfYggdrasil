// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Data/YggStructData.h"
#include "HeroAttributeComponent.generated.h"

/**
 *	김성훈
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboChanged);

class UDataTable;
UCLASS()
class HEROESOFYGGDRASIL_API UHeroAttributeComponent : public UCharacterAttributeComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere)
	UDataTable* Data;

	UPROPERTY(BlueprintReadOnly)
	float SpeedRate = 1.0f;
	UPROPERTY(BlueprintReadOnly)
	float JumpRate = 1.0f;
		
private:
};
