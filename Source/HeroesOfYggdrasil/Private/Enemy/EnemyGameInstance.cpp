// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyGameInstance.h"
#include "Data/YggStructData.h"

UEnemyGameInstance::UEnemyGameInstance()
{
	UE_LOG(LogTemp, Log, TEXT("%S(%u)> DataTableLoading Start"), __FUNCTION__, __LINE__);

	{
		FString DataPath = TEXT("/Script/Engine.DataTable'/Game/BP/Global/Data/DT_GlobalDataTable.DT_GlobalDataTable'");
		ConstructorHelpers::FObjectFinder<UDataTable> FinderDataTables(*DataPath);
		if (true == FinderDataTables.Succeeded())
		{
			DataTables = FinderDataTables.Object;
		}

		if (nullptr != DataTables)
		{
			MonsterDataTable = DataTables->FindRow<FDataTableRow>("DT_MonsterDataTable", nullptr)->Resources;
			if (nullptr == MonsterDataTable)
			{
				UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == ItemDataTable)"), __FUNCTION__, __LINE__);
			}
		}

	}

	UE_LOG(LogTemp, Log, TEXT("%S(%u)> DataTableLoading End"), __FUNCTION__, __LINE__);

	Random.GenerateNewSeed();
}

UEnemyGameInstance::~UEnemyGameInstance()
{
}
