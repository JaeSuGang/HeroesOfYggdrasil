// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggSelectAbilityUserWidget.generated.h"

class UYggAbilityUserWidget;
class UCanvasPanel;
class UButton;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggSelectAbilityUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = YGG)
	void ExitButtonEvent();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void PlayPopupAnim();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void PlayRPopupAnim();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void OnClickSound();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* SelectAbilityPanel;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> AbilityUserWidgetClass;

	UPROPERTY()
	UYggAbilityUserWidget* Ability_0;

	UPROPERTY()
	UYggAbilityUserWidget* Ability_1;

	UPROPERTY()
	UYggAbilityUserWidget* Ability_2;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopupAnim;

	UPROPERTY(EditAnywhere, Category = YGG)
	USoundBase* ClickSound;
};
