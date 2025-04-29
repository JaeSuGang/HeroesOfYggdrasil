// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggFuelBarUserWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggFuelBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateFuelBar();


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* FuelBar;


};
