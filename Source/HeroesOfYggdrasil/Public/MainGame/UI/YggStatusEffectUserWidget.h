// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggStatusEffectUserWidget.generated.h"

class UProgressBar;
class UImage;
class UTexture2D;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggStatusEffectUserWidget : public UYggUserWidget
{
	GENERATED_BODY()


public:


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:



};