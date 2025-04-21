// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "Data/YggEnumData.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "YggStatusEffectUserWidget.generated.h"

class UYggDebuffUserWidget;
class UHorizontalBox;


/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggStatusEffectUserWidget : public UYggUserWidget
{
	GENERATED_BODY()


public:
	void UpdateDebuff(FOnTagsChangedParams OnTagsChangedParams);

	UFUNCTION(BlueprintCallable)
	UYggDebuffUserWidget* FindDebuffWidget(EStatusEffectType StatusEffectType);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(EditAnywhere, Category = "YGG")
	TSubclassOf<UUserWidget> DebuffUserWidgetClass;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* DebuffContainer;

	UPROPERTY()
	TArray<UYggDebuffUserWidget*> DebuffWidgets;
};