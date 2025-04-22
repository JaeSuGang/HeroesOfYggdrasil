// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggYHPBarUserWidget.generated.h"

class UProgressBar;
class UTextBlock;
class AYggdrasil;
class UCharacterAttributeComponent;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggYHPBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateHPBar();


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


private:
	AYggdrasil* Yggdrasil;
	
	UCharacterAttributeComponent* CAC;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Health;


};
