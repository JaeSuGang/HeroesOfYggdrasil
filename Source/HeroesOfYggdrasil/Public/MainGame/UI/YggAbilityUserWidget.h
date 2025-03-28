// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggAbilityUserWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;


/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggAbilityUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* AbilityImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityInfo;

	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;
};
