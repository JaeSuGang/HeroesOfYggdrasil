// AssortRock 


#include "MainGame/MainGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AMainGameHUD::BeginPlay()
{
	Super::BeginPlay();

	CurrentWidget = CreateWidget(GetWorld(), MainWidgetClass);
	if (!CurrentWidget)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	CurrentWidget->AddToViewport();

	this->PlayerOwner->SetInputMode(FInputModeUIOnly{});

	this->PlayerOwner->bShowMouseCursor = true;
}

void AMainGameHUD::ExitRoomButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("TitleLevel")));
}

void AMainGameHUD::StartButton()
{
	ShowMainGameWidget();
}

void AMainGameHUD::ReadyButton()
{
}

void AMainGameHUD::ShowLobbyWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	if (LobbyWidgetClass)
	{
		CurrentWidget = CreateWidget(GetWorld(), LobbyWidgetClass);
		if (!CurrentWidget)
			UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
		
		CurrentWidget->AddToViewport();
	}
}

void AMainGameHUD::ShowMainGameWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	if (MainGameWidgetClass)
	{
		CurrentWidget = CreateWidget(GetWorld(), MainGameWidgetClass);
		if (!CurrentWidget)
			UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

		CurrentWidget->AddToViewport();
	}

	this->PlayerOwner->SetInputMode(FInputModeGameAndUI{});
}
