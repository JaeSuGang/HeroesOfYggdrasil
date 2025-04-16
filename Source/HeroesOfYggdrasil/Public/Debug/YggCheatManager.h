// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "YggCheatManager.generated.h"

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Exec)
	void Upgrade(int index);

	UFUNCTION(Exec)
	void AddUpgradePoint(int a);

	UFUNCTION(Exec)
	void Victory();

	UFUNCTION(Exec)
	void Defeat();
};
