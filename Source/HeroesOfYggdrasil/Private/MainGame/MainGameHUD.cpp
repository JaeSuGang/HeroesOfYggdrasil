// AssortRock 


#include "MainGame/MainGameHUD.h"
#include "MainGame/MainGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
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
	AMainGameMode* MGM = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (MGM)
	{
		MGM->OnAllPlayersReady();
	}
}

void AMainGameHUD::ReadyButton()
{
}

void AMainGameHUD::ShowLobbyWidget()
{
	if (LobbyWidgetClass)
	{
		CurrentWidget = CreateWidget(GetWorld(), LobbyWidgetClass);
		if (!CurrentWidget)
			UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
		
		CurrentWidget->AddToViewport();
	}

	this->PlayerOwner->SetInputMode(FInputModeUIOnly{});

	this->PlayerOwner->bShowMouseCursor = true;
}

void AMainGameHUD::ShowMainGameWidget()
{
	if (MainGameWidgetClass)
	{
		CurrentWidget = CreateWidget(GetWorld(), MainGameWidgetClass);
		if (!CurrentWidget)
			UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

		AIM = Cast<UImage>(CurrentWidget->GetWidgetFromName(TEXT("AIM")));

		CurrentWidget->AddToViewport();
	}

	this->PlayerOwner->SetInputMode(FInputModeGameOnly{});

	this->PlayerOwner->bShowMouseCursor = false;
}

void AMainGameHUD::CloseCurrentWidget()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
}

void AMainGameHUD::EnableCrossHair(bool bIsVisible)
{
	if (MainGameWidgetClass)
	{
		if (bIsVisible)
		{
			AIM->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			AIM->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

