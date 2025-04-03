// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyGameInstance.h"
#include "Data/YggStructData.h"

UEnemyGameInstance::UEnemyGameInstance()
{
	UE_LOG(LogTemp, Log, TEXT("%S(%u)> DataTableLoading Start"), __FUNCTION__, __LINE__);

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/DT_EnemyDataTable.DT_EnemyDataTable'");
		ConstructorHelpers::FObjectFinder<UDataTable> FinderDataTables(*DataPath);
	
		if (true == FinderDataTables.Succeeded())
		{
			DataTables = FinderDataTables.Object;
		}

		if (nullptr != DataTables)
		{
			MonsterDataTable = DataTables->FindRow<FDataTableRow>("EnemyBaseStatusDataTable", nullptr)->Resources;
			if (nullptr == MonsterDataTable)
			{
				UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == EnemyBaseStatusDataTable)"), __FUNCTION__, __LINE__);
			}
		}

	}

	UE_LOG(LogTemp, Log, TEXT("%S(%u)> DataTableLoading End"), __FUNCTION__, __LINE__);

	Random.GenerateNewSeed();
}

UEnemyGameInstance::~UEnemyGameInstance()
{
}
