// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyManager.h"
#include "Data/YggStructData.h"
#include "Enemy/EnemyCharacter.h"

UEnemyManager::UEnemyManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor* UEnemyManager::CreateMonster(const FString& _ItemName, FVector _OriginPos)
{
	TSubclassOf<AEnemyCharacter> SubClass = UGlobalDataTable::GetEnemySpawnClass(GetWorld(), TEXT("BP_EnemyCharacter"));

	FTransform Trans;
	AEnemyCharacter* NewActor = GetWorld()->SpawnActorDeferred<AEnemyCharacter>(SubClass, Trans);
	if (nullptr == NewActor)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == ItemActor) Item Spawn Is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	NewActor->SetDataKey(_ItemName);
	Trans.SetLocation(_OriginPos);
	NewActor->FinishSpawning(Trans);
	AllEnemyCharacter.Add(NewActor);

	return NewActor;
}

void UEnemyManager::NetSyncMonster()
{
}


void UEnemyManager::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UEnemyManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

