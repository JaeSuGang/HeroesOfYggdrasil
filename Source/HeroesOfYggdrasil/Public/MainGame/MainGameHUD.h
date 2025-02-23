// AssortRock 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API AMainGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void ExitRoomButton();

	UFUNCTION(BlueprintCallable)
	void StartButton();

	UFUNCTION(BlueprintCallable)
	void ReadyButton();

	void ShowLobbyWidget();
	void ShowMainGameWidget();

public:
	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> MainGameWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSoftObjectPtr<UWorld> MainGameLevel;

	UUserWidget* CurrentWidget;
};
