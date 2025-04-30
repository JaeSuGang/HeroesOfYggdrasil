// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggLobbySelectUserWidget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggLobbySelectUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "YGG")
	void LeftButtonEvent();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void RightButtonEvent();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	FString GetTextBlockValue();

	UPROPERTY(meta = (BindWidget))
	UButton* LeftButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RightButton;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* Nickname;

protected:
	virtual void NativeOnInitialized() override;

private:
	APlayerController* OwnerPlayer;

	UPROPERTY(EditAnywhere, Category = YGG)
	USoundBase* ClickSound;
};
