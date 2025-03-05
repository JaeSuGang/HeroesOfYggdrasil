// AssortRock 


#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/MainGameMode.h"
#include "MainGame/UI/YggLobbyUserWidget.h"

#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainGame/StageManager.h"

void AMainGameHUD::BeginPlay()
{
	Super::BeginPlay();

	CurrentWidget = CreateWidget(GetWorld(), MainWidgetClass);
	if (!CurrentWidget)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	CurrentWidget->AddToViewport();

	Start = Cast<UButton>(CurrentWidget->GetWidgetFromName(TEXT("Start")));
	
	APlayerController* PC = GetOwningPlayerController();
	if (PC && !(PC->HasAuthority()))
	{
		if (!Start)
		{
			UE_LOG(LogTemp, Error, TEXT("StartButton을 찾을 수 없습니다! Blueprint에서 이름을 확인하세요."));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("StartButton이 정상적으로 가져와졌습니다!"));
		}

		Start->SetIsEnabled(false);
		Start->SetRenderOpacity(1.0f);  // 흐려지는 효과 제거
	}

	UYggLobbyUserWidget* LobbyUserWidget = Cast<UYggLobbyUserWidget>(CurrentWidget);

	LobbyUserWidget->AddPlayerToLobby();

	this->PlayerOwner->SetInputMode(FInputModeUIOnly{});

	this->PlayerOwner->bShowMouseCursor = true;
}

void AMainGameHUD::ExitRoomButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("TitleLevel")));
}

void AMainGameHUD::StartButton()
{
	AStageManager* SM = AStageManager::Get(GetWorld());

	if (SM)
	{
		SM->StartGame();
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

