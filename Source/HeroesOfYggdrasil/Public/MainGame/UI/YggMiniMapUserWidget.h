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
	void SetMiniMapCam(UTexture2D* Texture);

	UTexture2D* ConvertRenderTargetToTexture2D(UTextureRenderTarget2D* RenderTarget);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* MiniMap;

	UTexture2D* Texture2D;
};
