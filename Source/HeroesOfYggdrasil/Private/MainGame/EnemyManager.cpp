// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/EnemyManager.h"

#include "Net/UnrealNetwork.h"

#include "MainGame/MainGameState.h"
#include "Data/YggStructData.h"

#include "Enemy/EnemyCharacter.h"
#include "Enemy/EnemyAIController.h"

AEnemyManager::AEnemyManager()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
}

AEnemyManager* AEnemyManager::Get(UWorld* WorldContext)
{
	AMainGameState* MGS = WorldContext->GetGameState<AMainGameState>();
	if (MGS)
	{
		return MGS->GetEnemyManager();
	}

	return nullptr;
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	NetSyncMonster();

	DeadEnemyCount = 0;
}

void AEnemyManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnemyManager, CachedEnemyCount);
	DOREPLIFETIME(AEnemyManager, DeadEnemyCount);
	DOREPLIFETIME(AEnemyManager, AllEnemyCharacter);
}

AActor* AEnemyManager::CreateMonster(const FString& _MonsterName, FVector _OriginPos)
{
	TSubclassOf<AEnemyCharacter> SubClass = UGlobalDataTable::GetEnemySpawnClass(GetWorld(), _MonsterName);
	
	FTransform Trans;
	AEnemyCharacter* NewEnemyCharacter = GetWorld()->SpawnActorDeferred<AEnemyCharacter>(SubClass, Trans);
	
	if (nullptr == NewEnemyCharacter)
	{
		UE_LOG(LogTemp, Fatal, TEXT("%S(%u)> if (nullptr == EnemyActor) Enemy Spawn Is Nullptr"), __FUNCTION__, __LINE__);
		return nullptr;
	}

	NewEnemyCharacter->SetDataKey(_MonsterName);
	Trans.SetLocation(_OriginPos);
	NewEnemyCharacter->FinishSpawning(Trans);
	AEnemyAIController* AICon = Cast<AEnemyAIController>(NewEnemyCharacter->GetController());
	AddEnemyCharacter(NewEnemyCharacter);

	return NewEnemyCharacter;
}

void AEnemyManager::NetSyncMonster_Implementation()
{
	for (size_t i = 0; i < AllEnemyCharacter.Num(); i++)
	{
		int CurAnimation = static_cast<int>(AllEnemyCharacter[i]->GetEnemyAnimInstance()->GetCurAnimationType());
		AllEnemyCharacter[i]->ChangeAnimation_Multicast(CurAnimation);
	}
}

int AEnemyManager::GetNumOfEnemyCharacter()
{
	return  static_cast<int>((AllEnemyCharacter.Num()));
}

void AEnemyManager::OnRep_AllEnemyCharacter()
{
	OnEnemyCountDelegate.Broadcast(this);
}

void AEnemyManager::AddEnemyCharacter(AEnemyCharacter* NewEnemy)
{
	if (AllEnemyCharacter.Contains(NewEnemy)) return;

	AllEnemyCharacter.Add(NewEnemy);
	Server_RequestEnemyCount();
	/*if (HasAuthority())*/
	{
		OnRep_AllEnemyCharacter();
	}
}

void AEnemyManager::RemoveEnemyCharacter(AEnemyCharacter* Enemy)
{
	if (!AllEnemyCharacter.Contains(Enemy)) return;

	AllEnemyCharacter.Remove(Enemy);

	Server_RequestEnemyCount();
	
	if (HasAuthority())
	{
		OnRep_AllEnemyCharacter();
	}

	DeadEnemyCount++;

	if (HasAuthority())
	{
		OnRep_DeadEnemyCount();
	}
}

void AEnemyManager::Server_RequestEnemyCount_Implementation()
{
	CachedEnemyCount = AllEnemyCharacter.Num();

	OnEnemyCountReady(CachedEnemyCount);
}

bool AEnemyManager::Server_RequestEnemyCount_Validate()
{
	return true;
}

void AEnemyManager::OnEnemyCountReady(int Count)
{
	// 블루프린트로 전달되거나 UI 반영
	UE_LOG(LogTemp, Log, TEXT("Enemy Count = %d"), Count);
}

void AEnemyManager::OnRep_EnemyCount()
{
	OnEnemyCountReady(CachedEnemyCount);
}

void AEnemyManager::OnRep_DeadEnemyCount()
{
	OnEnemyRemovedDelegate.Broadcast(this);;
}