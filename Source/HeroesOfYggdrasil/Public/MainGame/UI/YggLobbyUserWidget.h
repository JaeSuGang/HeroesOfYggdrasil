// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "YggLobbyUserWidget.generated.h"

class UCanvasPanel;
class UYggLobbySelectUserWidget;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggLobbyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void AddPlayerToLobby();

private:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* LobbyCanvasPanel;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UYggLobbySelectUserWidget> SelectUserWidgetClass;

	TArray<UYggLobbySelectUserWidget*> LobbySelectWidget{nullptr, 4};

	float WidgetSpace = 100.0f;
};
