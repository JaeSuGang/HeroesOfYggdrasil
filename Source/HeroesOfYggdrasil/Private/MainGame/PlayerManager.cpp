// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/PlayerManager.h"

#include "MainGame/MainGameState.h"
#include "MainGame/MainGamePlayerState.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"

APlayerManager::APlayerManager()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
}

APlayerManager* APlayerManager::Get(UWorld* WorldContext)
{
	if (AMainGameState* MGS = WorldContext->GetGameState<AMainGameState>())
	{
		return MGS->PlayerManager;
	}

	return nullptr;
}

AMainGamePlayerState* APlayerManager::GetPlayerState(APlayerController* PC)
{
	return PC->GetPlayerState<AMainGamePlayerState>();
}

void APlayerManager::Server_UpgradeAttack_Implementation(APlayerController* PC)
{
	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float PrevValue = HAC->GetAttackPoints();

			FCharacterUpgradeInfoRow* FoundRow = UpgradeTable->FindRow<FCharacterUpgradeInfoRow>(CHARACTER_UPGRADE_INFO_ROW_ATTACK, TEXT("Casting"));

			HAC->Server_SetAttackPoints(PrevValue + FoundRow->ValueIncrementPerUpgrade);
		}
	}
}

void APlayerManager::Server_UpgradeDefense_Implementation(APlayerController* PC)
{
	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float PrevValue = HAC->GetDefensePoints();

			FCharacterUpgradeInfoRow* FoundRow = UpgradeTable->FindRow<FCharacterUpgradeInfoRow>(CHARACTER_UPGRADE_INFO_ROW_DEFENSE, TEXT("Casting"));

			HAC->Server_SetDefensePoints(PrevValue + FoundRow->ValueIncrementPerUpgrade);
		}
	}
}

void APlayerManager::Server_UpgradeHealth_Implementation(APlayerController* PC)
{
	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float PrevValue = HAC->GetMaxHP();

			FCharacterUpgradeInfoRow* FoundRow = UpgradeTable->FindRow<FCharacterUpgradeInfoRow>(CHARACTER_UPGRADE_INFO_ROW_HEALTH, TEXT("Casting"));

			HAC->Server_SetMaxHP(PrevValue + FoundRow->ValueIncrementPerUpgrade);
		}
	}
}

void APlayerManager::Server_UpgradeMoveSpeed_Implementation(APlayerController* PC)
{
	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float PrevValue = HAC->GetMaxMoveSpeed();

			FCharacterUpgradeInfoRow* FoundRow = UpgradeTable->FindRow<FCharacterUpgradeInfoRow>(CHARACTER_UPGRADE_INFO_ROW_MOVE_SPEED, TEXT("Casting"));

			HAC->Server_SetMaxMoveSpeed(PrevValue + FoundRow->ValueIncrementPerUpgrade);
		}
	}
}

void APlayerManager::Server_UpgradeAttackSpeed_Implementation(APlayerController* PC)
{
	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float PrevValue = HAC->GetAttackSpeedRate();

			FCharacterUpgradeInfoRow* FoundRow = UpgradeTable->FindRow<FCharacterUpgradeInfoRow>(CHARACTER_UPGRADE_INFO_ROW_HEALTH, TEXT("Casting"));

			HAC->Server_SetAttackSpeedRate(PrevValue + FoundRow->ValueIncrementPerUpgrade);
		}
	}
}

int APlayerManager::GetUpgradePoints(APlayerController* Player) const
{
	if (AMainGamePlayerState* MPS = Player->GetPlayerState<AMainGamePlayerState>())
	{
		return MPS->GetUpgradePoints();
	}

	UE_LOG(LogTemp, Warning, TEXT("%S%u : PlayerState Casting Error Occured."), __FUNCTION__, __LINE__);
	return 0;
}



void APlayerManager::Server_AddUpgradePoints_Implementation(APlayerController* Player, int PointsToAdd)
{
	if (AMainGamePlayerState* MPS = Player->GetPlayerState<AMainGamePlayerState>())
	{
		MPS->AddUpgradePoints(PointsToAdd);
	}

	UE_LOG(LogTemp, Warning, TEXT("%S%u : PlayerState Casting Error Occured."), __FUNCTION__, __LINE__);
}

void APlayerManager::Server_SetUpgradePoints_Implementation(APlayerController* Player, int PointsToSet)
{
	if (AMainGamePlayerState* MPS = Player->GetPlayerState<AMainGamePlayerState>())
	{
		MPS->SetUpgradePoints(PointsToSet);
	}

	UE_LOG(LogTemp, Warning, TEXT("%S%u : PlayerState Casting Error Occured."), __FUNCTION__, __LINE__);
}

