// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "EnemyManager.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyCountDelegate, AEnemyManager*, _Manager);

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

	UFUNCTION(BlueprintCallable)
	int GetNumOfEnemyCharacter();
	
	UFUNCTION(BlueprintCallable)
	void AddEnemyCharacter(AEnemyCharacter* NewEnemy);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyCharacter(AEnemyCharacter* Enemy);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_RequestEnemyCount();

	UFUNCTION()
	void OnEnemyCountReady(int Count);

	UFUNCTION()
	void OnRep_EnemyCount();

protected:
	virtual void BeginPlay() override;

public:
	AActor* CreateMonster(const FString& _MonsterName, FVector _OriginPos);

	TArray<class AEnemyCharacter*> AllEnemyCharacter;

	UPROPERTY(ReplicatedUsing = OnRep_EnemyCount)
	int32 CachedEnemyCount;

	


	UPROPERTY(BlueprintAssignable, Category = "EnemyManager")
	FOnEnemyCountDelegate OnEnemyCountDelegate;
};
