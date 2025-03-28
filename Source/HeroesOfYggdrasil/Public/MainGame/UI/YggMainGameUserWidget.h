// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YggMainGameUserWidget.generated.h"

class UCanvasPanel;
class UYggPlayerStatusUserWidget;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggMainGameUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UYggPlayerStatusUserWidget* GetPlayerStatusWidget()
	{
		return PlayerStatusWidget;
	}


protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainGamePanel;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> PlayerStatusUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> OrderStatusUserWidgetClass;

	UYggPlayerStatusUserWidget* PlayerStatusWidget;

};
