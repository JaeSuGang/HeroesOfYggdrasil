// AssortRock 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainGameHUD.generated.h"

class UYggLobbyUserWidget;
class UYggMainGameUserWidget;
class UYggMHPBarUserWidget;
class AEnemyCharacter;

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
	void PlusButtonEvent();

	UFUNCTION(BlueprintCallable)
	void AbilitySelectEvent();

	UFUNCTION(BlueprintCallable)
	void EnableCrossHair(bool bIsVisible);

	UFUNCTION(BlueprintCallable)
	void CreateMHPBar(AEnemyCharacter* Enemy);

	UYggMainGameUserWidget* GetMainGameWidget()
	{
		return MainGameUserWidget;
	}

	//UFUNCTION(BlueprintCallable)
	//UYggMHPBarUserWidget* GetMHPBarWidget()
	//{
	//	return MHPBarUserWidget;
	//}

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

	/*UPROPERTY()
	UYggMHPBarUserWidget* MHPBarUserWidget;*/

	APlayerController* PC;

	UFUNCTION(BlueprintCallable)
	void SetSkillIcon(FName CharacterName);






	//TFunction<void()> StartButtinPlayerFunc;
	//void BindStartButtinPlayerFunc(TFunction<void()> _StartButtinPlayerFunc);
};
