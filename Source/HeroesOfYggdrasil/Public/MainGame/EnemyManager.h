// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "EnemyManager.generated.h"

/**
 * 담당 : 김경민, 장시혁
 */
UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API AEnemyManager : public AInfo
{
	GENERATED_BODY()

public:
	AEnemyManager();

	UFUNCTION(BlueprintCallable)
	static AEnemyManager* Get(UWorld* WorldContext);

public:
	UFUNCTION(Server, Reliable)
	void NetSyncMonster();

protected:
	virtual void BeginPlay() override;

public:
	AActor* CreateMonster(const FString& _MonsterName, FVector _OriginPos);

	TArray<class AEnemyCharacter*> AllEnemyCharacter;
};
