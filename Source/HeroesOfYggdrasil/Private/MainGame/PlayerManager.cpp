// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/PlayerManager.h"

APlayerManager::APlayerManager(const FObjectInitializer& ObjectInitializer)
	:
	Super(ObjectInitializer)
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
}
