// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YggLobbyUserWidget.generated.h"

class UCanvasPanel;
class UButton;
class UYggLobbySelectUserWidget;
class UYggUserWidget;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggLobbyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = YGG)
	void AddPlayerToLobby();

	void SetPlayerName();

	FString GetPlayerName()
	{
		return PlayerName;
	}

protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* LobbyCanvasPanel;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> SelectUserWidgetClass;

	UYggLobbySelectUserWidget* NewPlayerWidget;

	FString PlayerName;
};
