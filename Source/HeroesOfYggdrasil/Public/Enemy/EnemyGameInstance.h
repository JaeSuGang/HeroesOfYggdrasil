// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggGameInstance.h"
#include "EnemyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UEnemyGameInstance : public UYggGameInstance
{
	GENERATED_BODY()

	friend class UGlobalDataTable;

public:
	UEnemyGameInstance();
	~UEnemyGameInstance();

	// 언리얼이 인식하게 만들어서 
	UFUNCTION(BlueprintCallable, Category = "YggRandom")
	FRandomStream& GetRandom()
	{
		return Random;
	}

private:
	UPROPERTY(VisibleAnywhere, Category = "YggData")
	class UDataTable* DataTables = nullptr;
	
	class UDataTable* MonsterDataTable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "YggData")
	FRandomStream Random;
};

