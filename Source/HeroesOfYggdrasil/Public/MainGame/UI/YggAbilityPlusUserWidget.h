// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggAbilityPlusUserWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggAbilityPlusUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = YGG)
	void PlusButtonEvent();

protected:
	void NativeOnInitialized() override;


private:
	UPROPERTY(meta = (BindWidget))
	UButton* PlusButton;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> AbilityWidgetClass;
};
