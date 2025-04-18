// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MainGame/MainGamePlayerState.h"

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

	UFUNCTION(BlueprintCallable, Category = YGG)
	void StartAbilityPlus();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void EndAbilityPlus();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void CreateAbility();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void DelSelectAbility();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void TempFunc();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainGamePanel;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityPlusButton;

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
};
