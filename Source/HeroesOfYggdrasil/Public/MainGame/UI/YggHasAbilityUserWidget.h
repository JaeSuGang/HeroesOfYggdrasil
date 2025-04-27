// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggHasAbilityUserWidget.generated.h"

class UImage;
class UButton;
class UYggTooltipUserWidget;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggHasAbilityUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	void EndHasAbility();

	UFUNCTION(BlueprintCallable)
	void UpdateWidget();

	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnUnHovered();

	int32 CurrentHoveredIndex = -1;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> TooltipWidgetClass;

	UPROPERTY()
	UYggTooltipUserWidget* CurTooltipWidget;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability0;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability1;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability2;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability3;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability4;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability5;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability6;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability7;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability8;

	UPROPERTY(meta = (BindWidget))
	UImage* Ability9;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton0;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton1;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton2;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton3;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton4;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton5;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton6;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton7;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton8;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityButton9;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	TArray<UImage*> Abilitys;
	TArray<UButton*> AbilityButtons;

	TMap<UButton*, int32> ButtonIndexMap;
};
