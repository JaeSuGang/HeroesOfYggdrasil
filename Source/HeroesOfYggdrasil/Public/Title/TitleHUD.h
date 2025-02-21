// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleHUD.generated.h"

class UUserWidget;

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API ATitleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATitleHUD(const FObjectInitializer& objectInitializer);

protected:
	void BeginPlay() override;


public:
	UFUNCTION(BlueprintCallable)
	void CreateRoom();

	UFUNCTION(BlueprintCallable)
	void JoinRoom(FString strIPAddress);

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> MainGameLevel;

	UPROPERTY(EditAnywhere, Category = YGG)
	FString DefaultPort;

	UUserWidget* MainWidgetInstance;
};
