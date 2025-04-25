// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggDefeatedUserWidget.generated.h"

class UTextBlock;
class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggDefeatedUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Init();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayTime;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurWave;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveProgress;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MDeathCount;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PDeathCount;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FirstAnim;
};
