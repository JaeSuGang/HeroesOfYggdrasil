
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/YggCharacter.h"
#include "Enemy/EnemyAnimCharacter.h"
#include "Data/YggEnumData.h"
#include "Data/YggStructData.h"
#include "EnemyCharacter.generated.h"

/**
 * 담당 : 장시혁
 */

class UCharacterAttributeComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AEnemyCharacter : public AEnemyAnimCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	const FMonsterDataRow* GetData()
	{
		return MonsterData;
	}

	void SetDataKey(const FString& _ItemDataKey)
	{
		DataKey = _ItemDataKey;
	}

	void SetEnemyAttributeComponent(UEnemyAttributeComponent* _EnemyAttributeComponent)
	{
		EnemyAttributeComponent = _EnemyAttributeComponent;
	}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
	void OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Replicated, Category = "YggData", meta = (AllowPrivateAccess = "true"))
	class UEnemyAttributeComponent* EnemyAttributeComponent = nullptr;

private:
	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FString DataKey = "Minion_0";

	const FMonsterDataRow* MonsterData = nullptr;

	UPROPERTY(Category = "YggData", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAIDataObject* AIData = nullptr;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "YggData", meta = (AllowPrivateAccess = "true"))
	EEnemyAIState CurAnimnation = EEnemyAIState::Idle;
};


