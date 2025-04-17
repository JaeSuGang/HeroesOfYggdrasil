// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggStatusEffectUserWidget.generated.h"

class UProgressBar;
class UImage;
class UTexture2D;

USTRUCT()
struct FUIStatusEffectData
{
	GENERATED_BODY()

	UPROPERTY()
	UProgressBar* Bar = nullptr;

	UPROPERTY()
	UImage* Image = nullptr;

	UPROPERTY()
	UTexture2D* Icon = nullptr;

	FTimerHandle TimerHandle;
	float CoolTime = 0.0f;
	float RemainingTime = 0.0f;
};

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggStatusEffectUserWidget : public UYggUserWidget
{
	GENERATED_BODY()


public:


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:



};