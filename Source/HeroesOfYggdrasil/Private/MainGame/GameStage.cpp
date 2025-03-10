// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/GameStage.h"

AGameStage::AGameStage()
{
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;

}

void AGameStage::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		this->OnEnterStage();
	}
}

void AGameStage::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Type::Destroyed)
	{
		if (HasAuthority())
		{
			this->OnExitStage();
		}
	}
}

void AGameStage::OnExitStage_Implementation()
{

}

void AGameStage::OnEnterStage_Implementation()
{

}
