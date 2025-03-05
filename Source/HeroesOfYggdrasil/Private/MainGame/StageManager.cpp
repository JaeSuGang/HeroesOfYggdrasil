// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/StageManager.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "MainGame/MainGameState.h"
#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/PlayerSelectZone.h"

void AStageManager::EnterStage_Implementation(EGameStage newStage, int nRound)
{
	this->OnExitStage();

	CurrentStage = newStage;
	Round = nRound;

	switch (newStage)
	{
	case EGameStage::PreStart:
		break;

	case EGameStage::Reinforce:
	{
		if (Round == 1)
		{
		}
	}
		break;
	case EGameStage::Battle:
		break;
	default:
		break;
	}
}

AStageManager* AStageManager::Get(UWorld* WorldContext)
{
	AMainGameState* MGS = WorldContext->GetGameState<AMainGameState>();
	if (MGS)
	{
		return MGS->GetStageManager();
	}

	return nullptr;
}

void AStageManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AStageManager, CurrentStage);
	DOREPLIFETIME(AStageManager, Round);
}

void AStageManager::StartGame_Implementation()
{
	this->EnterStage(EGameStage::Reinforce, 1);

	auto ControllerIter = GetWorld()->GetPlayerControllerIterator();
	while (ControllerIter)
	{
		APlayerController* PC = ControllerIter->Get();
		if (APlayerSelectZone* PSZ = Cast<APlayerSelectZone>(PC->GetPawn()))	
		{
			PSZ->SelectCharacter();
		}
		++ControllerIter;
	}

	ForceMainWidgetToClients();
}

void AStageManager::ForceMainWidgetToClients_Implementation()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (AMainGameHUD* MGH = Cast<AMainGameHUD>(PC->GetHUD()))
		{
			MGH->CloseCurrentWidget();
			MGH->ShowMainGameWidget();
		}
	}
}

void AStageManager::OnExitStage_Implementation()
{

}

void AStageManager::OnUpdateStage_Implementation()
{

}

AStageManager::AStageManager(const FObjectInitializer& ObjectInitializer)
	:
	Super(ObjectInitializer)
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
	Round = 0;
}

