// AssortRock 


#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/MainGameMode.h"
#include "MainGame/UI/YggLobbyUserWidget.h"
#include "MainGame/UI/YggMainGameUserWidget.h"
#include "MainGame/UI/YggNicknameBarUserWidget.h"
#include "MainGame/MainGamePlayerState.h"
#include "MainGame/PlayerManager.h"

#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/YggHero.h"
#include "NPC/Yggdrasil.h"

#include "MainGame/UI/YggMHPBarUserWidget.h"
#include "MainGame/UI/YggCastingBarUserWidget.h"
#include "MainGame/UI/YggSkillBarUserWidget.h"
#include "Enemy/EnemyCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "StageSystem/StageSystem.h"

#include "MainGame/MainGamePlayerState.h"

#include "UpgradeSystem/UpgradeSystem.h"
#include "UpgradeSystem/UpgradeDataAsset.h"

#include "EngineUtils.h"


void AMainGameHUD::BeginPlay()
{
	Super::BeginPlay();

	CurrentWidget = CreateWidget(GetWorld(), MainWidgetClass);
	if (!CurrentWidget)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	CurrentWidget->AddToViewport();

	Start = Cast<UButton>(CurrentWidget->GetWidgetFromName(TEXT("Start")));

	PC = GetOwningPlayerController();
	if (PC && !(PC->HasAuthority()))
	{
		if (!Start)
		{
			UE_LOG(LogTemp, Error, TEXT("Start을 찾을 수 없습니다! Blueprint에서 이름을 확인하세요."));
		}

		Start->SetIsEnabled(false);
	}

	LobbyUserWidget = Cast<UYggLobbyUserWidget>(CurrentWidget);

	LobbyUserWidget->AddPlayerToLobby();

	this->PlayerOwner->SetInputMode(FInputModeUIOnly{});

	this->PlayerOwner->bShowMouseCursor = true;

	TActorIterator<AYggdrasil> iter(GetWorld());

	Yggdrasil = *iter;
}

void AMainGameHUD::OnStartGame(FOnGameStartParams OnGameStarted)
{
	CloseCurrentWidget();
	ShowMainGameWidget();
}

void AMainGameHUD::ExitRoomButton()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("TitleLevel")));
}

void AMainGameHUD::StartButton()
{
	UStageSystem* StageSystem =	UStageSystem::Get(GetWorld());
	
	LobbyUserWidget->SetPlayerName();

	AMainGamePlayerState* PS = PC->GetPlayerState<AMainGamePlayerState>();
	PS->ServerSetPlayerName(LobbyUserWidget->GetPlayerName());

	if (StageSystem)
	{
		StageSystem->StartGame();
	}
}

void AMainGameHUD::ReadyButton()
{
	LobbyUserWidget->SetPlayerName();

	AMainGamePlayerState* PS = PC->GetPlayerState<AMainGamePlayerState>();
	PS->ServerSetPlayerName(LobbyUserWidget->GetPlayerName());
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
	CloseCurrentWidget();

	if (MainGameWidgetClass)
	{
		MainGameUserWidget = CreateWidget<UYggMainGameUserWidget>(GetWorld(), MainGameWidgetClass);
		CurrentWidget = MainGameUserWidget;
		if (!CurrentWidget)
			UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

		AIM = Cast<UImage>(CurrentWidget->GetWidgetFromName(TEXT("AIM")));

		PC = GetWorld()->GetFirstPlayerController();
		AMainGamePlayerState* PS = PC->GetPlayerState<AMainGamePlayerState>();
	
		if (!PS->OnUpgradePointsChanged.IsAlreadyBound(this, &AMainGameHUD::OnUpgradePointChange))
		{
			PS->OnUpgradePointsChanged.AddDynamic(this, &AMainGameHUD::OnUpgradePointChange);
		} 

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

void AMainGameHUD::AbilitySelectEvent()
{
	if (MainGameWidgetClass)
	{
		MainGameUserWidget = Cast<UYggMainGameUserWidget>(CurrentWidget);

		MainGameUserWidget->DelSelectAbility();
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

void AMainGameHUD::OnUpgradePointChange(FOnUpgradePointsChangedParams OnUpgradePointsChangedParams)
{
	if (0 < OnUpgradePointsChangedParams.NewUpgradePoints)
	{
		MainGameUserWidget->StartAbilityPlus();
	}
	else
	{
		MainGameUserWidget->EndAbilityPlus();
	}
}