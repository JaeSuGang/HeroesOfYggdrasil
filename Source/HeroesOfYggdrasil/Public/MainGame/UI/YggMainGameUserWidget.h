// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YggMainGameUserWidget.generated.h"

class UCanvasPanel;
class UYggPlayerStatusUserWidget;
class UYggOrderStatusUserWidget;
class UYggAbilityPlusUserWidget;
class UYggAbilityUserWidget;
class UYggCastingBarUserWidget;
class UYggSkillBarUserWidget;

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
	void CreateAbilityPlus();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void CreateAbility();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void DelAbilityPlus();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void DelAbility();


protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MainGamePanel;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> PlayerStatusUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> OrderStatusUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> AbilityPlusUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> AbiltyUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> CastingBarUserWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> SkillBarUserWidgetClass;

	UPROPERTY()
	UYggPlayerStatusUserWidget* PlayerStatusWidget;

	UPROPERTY()
	UYggOrderStatusUserWidget* OrderStatusWidget;
	
	UPROPERTY()
	UYggAbilityPlusUserWidget* AbilityPlusWidget;

	UPROPERTY()
	UYggAbilityUserWidget* AbilityWidget;

	UPROPERTY()
	UYggCastingBarUserWidget* CastingBarWidget;

	UPROPERTY()
	UYggSkillBarUserWidget* SkillBarWidget;

};
