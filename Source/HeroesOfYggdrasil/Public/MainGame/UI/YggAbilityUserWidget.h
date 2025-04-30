// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "UpgradeSystem/UpgradeDataAsset.h"
#include "YggAbilityUserWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;
class UUpgradeDataAsset;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggAbilityUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void AbilityInit(FPrimaryAssetId& AssetId);

	UFUNCTION(BlueprintCallable)
	void AbilitySelectEvent();

	FSlateBrush MakeBrush(UTexture2D* Tex, FVector2D Size);

	UUpgradeDataAsset* GetUpgradeDataAsset()
	{
		return UpgradeDataAsset;
	}

	UFUNCTION(BlueprintCallable)
	void ApplyRarityEffect(EUpgradeRarity Rarity);

	UFUNCTION(BlueprintCallable)
	void PlayHoverAnim();

	UFUNCTION(BlueprintCallable)
	void PlayUnHoverAnim();

	UFUNCTION(BlueprintCallable)
	void OnClickSound();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* AbilityImage;

	UPROPERTY(meta = (BindWidget))
	UImage* Background;

	UPROPERTY(meta = (BindWidget))
	UImage* Edge;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityInfo;

	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY()
	UUpgradeDataAsset* UpgradeDataAsset;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UMaterialInterface* EdgeMaterial;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopupAnim;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* HoverAnim;

	UPROPERTY(EditAnywhere, Category = YGG)
	USoundBase* ClickSound;
};
