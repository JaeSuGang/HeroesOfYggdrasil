// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggMiniMapUserWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggMiniMapUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetMiniMapCam();
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* MiniMap;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UMaterialInterface* MaskedMaterial;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UTexture2D* CircleMaskTexture;

	UPROPERTY()
	UMaterialInstanceDynamic* MiniMapMatInst;

	UTexture2D* Texture2D;
};
