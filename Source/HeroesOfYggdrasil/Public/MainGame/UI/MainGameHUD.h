// AssortRock 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "StageSystem/StageSystem.h"

#include "MainGame/MainGamePlayerState.h"

#include "MainGameHUD.generated.h"

class UYggLobbyUserWidget;
class UYggMainGameUserWidget;
class UYggMHPBarUserWidget;
class AEnemyCharacter;
class AYggdrasil;
class UYggMiniMapManager;

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
	UFUNCTION()
	void OnStartGame(FOnGameStartParams OnGameStarted);

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
	void AbilitySelectEvent();

	UFUNCTION(BlueprintCallable)
	void EnableCrossHair(bool bIsVisible);

	UFUNCTION()
	void OnUpgradePointChange(FOnUpgradePointsChangedParams OnUpgradePointsChangedParams);

	UYggMainGameUserWidget* GetMainGameWidget()
	{
		return MainGameUserWidget;
	}

	AYggdrasil* GetYggdrasil()
	{
		return Yggdrasil;
	}

public:
	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> LobbyWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> MainGameWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> MHPBarWidgetClass;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSoftObjectPtr<UWorld> MainGameLevel;

	UPROPERTY(meta = (BindWidget))
	class UImage* AIM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* Start;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = YGG)
	UUserWidget* CurrentWidget;

	UPROPERTY()
	UYggLobbyUserWidget* LobbyUserWidget;

	UPROPERTY()
	UYggMainGameUserWidget* MainGameUserWidget;

	UPROPERTY()
	APlayerController* PC;

	UPROPERTY()
	AYggdrasil* Yggdrasil;

	UPROPERTY()
	UYggMiniMapManager* MiniMapManager;
};
