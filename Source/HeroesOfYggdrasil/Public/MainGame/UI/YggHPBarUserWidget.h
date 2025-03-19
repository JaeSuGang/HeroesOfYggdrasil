// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggHPBarUserWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggHPBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void UpdateHPBar(float HP);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;
};
