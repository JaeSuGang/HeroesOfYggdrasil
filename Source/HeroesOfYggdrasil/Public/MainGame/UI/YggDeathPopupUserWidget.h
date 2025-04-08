// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggDeathPopupUserWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggDeathPopupUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:



protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;


private:
	UProgressBar* RespawnBar;
	UTextBlock* CountBlock;

};
