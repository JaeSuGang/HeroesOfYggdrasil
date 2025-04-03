
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/YggCharacter.h"
#include "Enemy/EnemyAnimCharacter.h"
#include "Data/YggEnumData.h"
#include "Data/YggStructData.h"
#include "Enemy/Interface/AttackInterface.h"
#include "EnemyCharacter.generated.h"

class AYggMiniMapIconActor;

/**
 * 담당 : 장시혁
 */

class UCharacterAttributeComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AEnemyCharacter : public AEnemyAnimCharacter, public IAttackInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	UFUNCTION()
	void OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void AttackStart() override;

	void AttackEnd() override;

	const FMonsterDataRow* GetData()
	{
		return MonsterData;
	}

	void SetDataKey(const FString& _MonsterDataKey)
	{
		DataKey = _MonsterDataKey;
	}

	UFUNCTION(BlueprintCallable)
	double GetCurHp()
	{
		return AIData->PlayData.CurHP;
	}
	
	FString GetDataKey()
	{
		return DataKey;
	}

	UFUNCTION(BlueprintCallable)
	void SpawnAndFireArrow();

	UFUNCTION(BlueprintCallable)
	void HideArrow();

	UFUNCTION(BlueprintCallable)
	void RevealArrow();

	UFUNCTION(BlueprintCallable)
	void SpawnWarningRange(AActor* _Actor);

	UFUNCTION(BlueprintCallable)
	void SpawnWarningOutRange(AActor* _Actor);

	UFUNCTION(BlueprintCallable)
	void SpawnWarningInRange(AActor* _Actor);

	UFUNCTION(BlueprintCallable)
	void ThrowPoisonedBall(FVector _TargetLocation);

	UFUNCTION(BlueprintCallable)
	class AEnemyWarningRange* GetWarningIntRangeClass()
	{
		return WarningInRangeClass;
	}


protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AEnemyProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AEnemyRangeAttack> RangeAttackClass;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAOE")
	TSubclassOf<class AEnemyWarningRange> WarningOutRangeClass;

	UPROPERTY(EditDefaultsOnly, Category = "EnemyAOE")
	class AEnemyWarningRange* WarningInRangeClass;


private:
	// 몬스터 이름 데이터
	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	FString DataKey = "";

	const FMonsterDataRow* MonsterData = nullptr;

	UPROPERTY(Category = "YggData", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAIDataObject* AIData = nullptr;

	// 애니메이션
	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "YggData", meta = (AllowPrivateAccess = "true"))
	EEnemyAIState CurAnimnation = EEnemyAIState::Idle;

	UPROPERTY(EditDefaultsOnly, Category = "YggMiniMapIcon")
	TSubclassOf<AYggMiniMapIconActor> MiniMapIconClass;


};


