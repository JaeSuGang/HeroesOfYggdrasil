// AssortRock 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainGameHUD.generated.h"

class APlayerSelectZone;

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

	UFUNCTION(BlueprintCallable)
	void ShowLobbyWidget();

	UFUNCTION(BlueprintCallable)
	void ShowMainGameWidget();

	UFUNCTION(BlueprintCallable)
	void CloseCurrentWidget();

	UFUNCTION(BlueprintCallable)
	void EnableCrossHair(bool bIsVisible);

public:
	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> MainGameWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSoftObjectPtr<UWorld> MainGameLevel;

	UPROPERTY(meta = (BindWidget))
	class UImage* AIM;

	
	UUserWidget* CurrentWidget;
};
