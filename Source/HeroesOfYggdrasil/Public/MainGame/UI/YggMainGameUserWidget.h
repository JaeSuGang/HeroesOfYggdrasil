// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MainGame/MainGamePlayerState.h"
#include "StageSystem/StageSystem.h"

#include "YggMainGameUserWidget.generated.h"


class UCanvasPanel;
class UButton;
class UYggPlayerStatusUserWidget;
class UYggOrderStatusUserWidget;
class UYggAbilityPlusUserWidget;
class UYggAbilityUserWidget;
class UYggSelectAbilityUserWidget;
class UYggCastingBarUserWidget;
class UYggSkillBarUserWidget;
class UYggDeathPopupUserWidget;
class UYggStatusUserWidget;
class UTextBlock;
class UStageBase;
class UYggFuelBarUserWidget;
class UYggVictoryUserWidget;
class UYggDefeatedUserWidget;
class UYggHasAbilityUserWidget;

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

	UYggCastingBarUserWidget* GetCastingBarWidget()
	{
		return CastingBarWidget;
	}

	UYggSkillBarUserWidget* GetSkillBarWidget()
	{
		return SkillBarWidget;
	}

	UYggHasAbilityUserWidget* GetHasAbilityWidget()
	{
		return HasAbilityWidget;
	}

	UFUNCTION(BlueprintCallable, Category = YGG)
	void StartAbilityPlus();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void EndAbilityPlus();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void CreateAbility();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void DelSelectAbility();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void StatusVisibility();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void UpdateWaveCount(UStageBase* NewStage);

	UFUNCTION()
	void ChildWidgetHidden(FOnDefeatedParams OnDefeatedParams);

	UFUNCTION()
	void CreateVictoryWidget(FOnVictoryParams OnVictoryParams);

	UFUNCTION()
	void CreateDefeatedWidget();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainGamePanel;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityPlusButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveCount;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> PlayerStatusUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> OrderStatusUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> AbilityUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> SelectAbilityUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> CastingBarUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> SkillBarUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> DeathPopupWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> StatusWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> FuelBarWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> VictoryWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> DefeatedWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> HasAbilityWidgetClass;

	UPROPERTY()
	UYggPlayerStatusUserWidget* PlayerStatusWidget;

	UPROPERTY()
	UYggOrderStatusUserWidget* OrderStatusWidget;

	UPROPERTY()
	UYggAbilityUserWidget* AbilityWidget;

	UPROPERTY()
	UYggSelectAbilityUserWidget* SelectAbilityWidget = nullptr;

	UPROPERTY()
	UYggCastingBarUserWidget* CastingBarWidget;

	UPROPERTY()
	UYggSkillBarUserWidget* SkillBarWidget;

	UPROPERTY()
	UYggDeathPopupUserWidget* DeathPopupWidget;

	UPROPERTY()
	UYggStatusUserWidget* StatusWidget;

	UPROPERTY()
	UYggFuelBarUserWidget* FuelBarWidget;

	UPROPERTY()
	UYggVictoryUserWidget* VictoryWidget;

	UPROPERTY()
	UYggDefeatedUserWidget* DefeatedWidget;

	UPROPERTY()
	UYggHasAbilityUserWidget* HasAbilityWidget;
};
