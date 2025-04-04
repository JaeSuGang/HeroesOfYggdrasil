// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggCastingBarUserWidget.generated.h"

class UProgressBar;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggCastingBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	

public:
	void NativeOnInitialized() override;
	void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void StartCasting(float Duration);

	UFUNCTION(BlueprintCallable)
	void UpdateCastingBar();

	UFUNCTION(BlueprintCallable)
	void EndCasting();

	FTimerHandle CastingTimerHandle;
	float CastingTime;
	float RemainingTime;

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* CastingBar;
};
