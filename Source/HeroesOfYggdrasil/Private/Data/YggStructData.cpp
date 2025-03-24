// Coded By AssortRock Unreal Engine Class Project


#include "Data/YggStructData.h"
#include "Enemy/EnemyCharacter.h"
#include "Enemy/EnemyGameInstance.h"





TSubclassOf<AEnemyCharacter> UGlobalDataTable::GetEnemySpawnClass(UWorld* _World, const FString& _Name)
{
	UEnemyGameInstance* Inst = _World->GetGameInstance<UEnemyGameInstance>();

	if (nullptr == Inst->MonsterDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Inst->MonsterDataTable)"), __FUNCTION__, __LINE__);
	}

	FMonsterDataRow* Data = Inst->MonsterDataTable->FindRow<FMonsterDataRow>(*_Name, nullptr);
	
	return *Data->SpawnClass;
}

const FMonsterDataRow UGlobalDataTable::GetMonsterData(UWorld* _World, const FString& _Name)
{
	UEnemyGameInstance* Inst = _World->GetGameInstance<UEnemyGameInstance>();

	if (nullptr == Inst->MonsterDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Inst->MonsterDataTable)"), __FUNCTION__, __LINE__);
	}

	FMonsterDataRow* Data = Inst->MonsterDataTable->FindRow<FMonsterDataRow>(*_Name, nullptr);

	return *Data;
}
