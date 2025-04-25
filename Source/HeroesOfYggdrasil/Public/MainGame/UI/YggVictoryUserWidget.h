// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggVictoryUserWidget.generated.h"

class UTextBlock;
class UTexture2D;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggVictoryUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* sdf;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* sdfsdfdf;

};
