// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggLobbySelectUserWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggLobbySelectUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void LeftButtonEvent();

	UFUNCTION(BlueprintCallable)
	void RightButtonEvent();

	UPROPERTY(meta = (BindWidget))
	UButton* LeftButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RightButton;

protected:
	virtual void NativeOnInitialized() override;

private:
	APlayerController* OwnerPlayer;
};
