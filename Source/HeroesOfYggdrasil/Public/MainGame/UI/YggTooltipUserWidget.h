// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggTooltipUserWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggTooltipUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetTipText(const FText& NameText, const FText& DescriptionText);


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Tooltip;


};
