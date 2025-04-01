// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PaperSpriteComponent.h"
#include "YggUIDataAsset.generated.h"


/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggUIDataAsset : public UDataAsset
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TMap<FName, UPaperSprite*> IconSetting;
};
