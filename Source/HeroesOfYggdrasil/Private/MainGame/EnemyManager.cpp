// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/EnemyManager.h"
#include "Data/YggStructData.h"
#include "Enemy/EnemyCharacter.h"

AEnemyManager::AEnemyManager()
{

}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	NetSyncMonster();
}

AActor* AEnemyManager::CreateMonster(const FString& _MonsterName, FVector _OriginPos)
{
	TSubclassOf<AEnemyCharacter> SubClass = UGlobalDataTable::GetEnemySpawnClass(GetWorld(), _MonsterName);

	FTransform Trans;
	AEnemyCharacter* NewEnemyCharacter = GetWorld()->SpawnActorDeferred<AEnemyCharacter>(SubClass, Trans);
	if (nullptr == NewEnemyCharacter)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == ItemActor) Item Spawn Is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	NewEnemyCharacter->SetDataKey(_MonsterName);
	Trans.SetLocation(_OriginPos);
	NewEnemyCharacter->FinishSpawning(Trans);
	AllEnemyCharacter.Add(NewEnemyCharacter);

	return NewEnemyCharacter;
}

void AEnemyManager::NetSyncMonster_Implementation()
{
	for (size_t i = 0; i < AllEnemyCharacter.Num(); i++)
	{
		int CurAnimation = static_cast<int>(AllEnemyCharacter[i]->GetGMAnimInstance()->GetCurAnimationType());
		AllEnemyCharacter[i]->ChangeAnimation_Multicast(CurAnimation);
	}
}


