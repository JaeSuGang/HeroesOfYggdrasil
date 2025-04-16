// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggAbilityUserWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;
class UUpgradeDataAsset;


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

	UUpgradeDataAsset* GetUpgradeDataAsset()
	{
		return UpgradeDataAsset;
	}

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* AbilityImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AbilityInfo;

	UPROPERTY(meta = (BindWidget))
	UButton* SelectButton;

	UPROPERTY(EditAnywhere)
	UUpgradeDataAsset* UpgradeDataAsset;
};
