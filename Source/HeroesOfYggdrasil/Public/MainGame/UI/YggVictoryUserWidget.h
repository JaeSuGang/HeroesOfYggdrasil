// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggVictoryUserWidget.generated.h"

class UTextBlock;
class UWidgetAnimation;
class UButton;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggVictoryUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void OnClickSound();

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

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FirstAnim;

	UPROPERTY(EditAnywhere, Category = YGG)
	USoundBase* ClickSound;
};
