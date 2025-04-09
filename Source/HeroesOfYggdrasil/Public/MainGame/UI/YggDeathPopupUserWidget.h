// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggDeathPopupUserWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggDeathPopupUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void StartRespawn(float Duration);

	UFUNCTION(BlueprintCallable)
	void UpdateRespawnBar();

	UFUNCTION(BlueprintCallable)
	void EndRespawn();

	FTimerHandle RespawnTimerHandle;
	float RespawnTime;
	float RemainingTime;


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;


private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* RespawnBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountBlock;

};
