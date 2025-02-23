// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/TitleHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ATitleHUD::ATitleHUD(const FObjectInitializer& objectInitializer)
{
	DefaultPort = TEXT("3019");
}

void ATitleHUD::BeginPlay()
{
	/* 블루프린트에서 지정해준 UUserWidget을 생성 */
	MainWidgetInstance = CreateWidget(GetWorld(), MainWidgetClass);
	if (!MainWidgetInstance)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	/* 화면에서 띄움 */
	MainWidgetInstance->AddToViewport();

	/* Input Mode 전환 */
	this->PlayerOwner->SetInputMode(FInputModeUIOnly{});

	/* 마우스 커서 보이게 하기 */
	this->PlayerOwner->bShowMouseCursor = true;
}

void ATitleHUD::CreateRoom()
{
	FString MainGameLevelName = MainGameLevel.GetLongPackageName();
	FString OpenLevel = FString::Printf(TEXT(":%s%s"), *DefaultPort, *MainGameLevelName);

	if (!MainGameLevelName.IsEmpty())
		UGameplayStatics::OpenLevel(GetWorld(), *OpenLevel, true, TEXT("listen"));
	else
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
}

void ATitleHUD::JoinRoom(FString strIPAddress)
{
	FString FinalUrl = FString::Printf(TEXT("%s:%s"), *strIPAddress, *DefaultPort);

	UGameplayStatics::OpenLevel(GetWorld(), *FinalUrl);
}

void ATitleHUD::EndGameButton()
{
	APlayerController* PlayerController = GetOwningPlayerController();

	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}