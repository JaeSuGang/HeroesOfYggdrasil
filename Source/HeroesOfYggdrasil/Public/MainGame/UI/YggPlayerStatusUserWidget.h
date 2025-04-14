// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggPlayerStatusUserWidget.generated.h"

class UImage;
class UProgressBar;
class UVerticalBox;
class UYggHPBarUserWidget;
class UYggNicknameBarUserWidget;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggPlayerStatusUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetFaceCam();


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* PlayerFace;
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> HPBarWidgetClass;

	UPROPERTY()
	UYggHPBarUserWidget* HPBarUserWidget;

	UTexture2D* Texture2D;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UMaterialInterface* MaskedMaterial;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UTexture2D* DiamondMaskTexture;

	UPROPERTY()
	UMaterialInstanceDynamic* FaceMatInst;

};
