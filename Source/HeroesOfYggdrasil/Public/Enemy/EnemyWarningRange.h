// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/YggStructData.h"
#include "EnemyWarningRange.generated.h"


class AYggTickActor;
class AEnemyCharacter;
class UCharacterAttributeComponent;
class UYggAttackCapsuleComponent;
class UStaticMeshComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;
class UNiagaraSystem;

UCLASS()
class HEROESOFYGGDRASIL_API AEnemyWarningRange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyWarningRange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void InitializeWarningRange();

	UFUNCTION()
	void ChangeArea();

	UFUNCTION()
	void SpawnEffect();
	
	UFUNCTION()
	void OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void SetCollisionOwnerEnemy(AEnemyCharacter* _Enemy);

	UFUNCTION()
	void HideAllComponents();

	UFUNCTION()
	FName GetMeshNameByKey(const FString& _DataString);

	float GetDuration()
	{
		return Duration;
	}

	float GetTimeElapsed()
	{
		return TimeElapsed;
	}

	class UYggAttackCapsuleComponent* GetRangeAttackCollision()
	{
		return RangeAttackCollision;
	}
	
public:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlaneMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* WarningMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	UDataTable* AOEDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	float TimeElapsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	UCharacterAttributeComponent* EnemyAttributeComponent;

	UPROPERTY(EditAnywhere, Category = "EnemyEffects")
	UParticleSystem* EffectParticle;  

	UPROPERTY(EditAnywhere, Category = "EnemyEffects")
	UNiagaraSystem* EnemyNiagaraSystem;

	UPROPERTY(EditAnywhere, Category = "EnemyEffects")
	AEnemyCharacter* YggCharacterEnemy;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FString DataKeyString;

	UPROPERTY(EditAnywhere, Category = "Tick")
	TSubclassOf<AYggTickActor> TickActorClass;

	UPROPERTY(EditAnywhere, Category = "EnemyCapsuleCollision")
	UYggAttackCapsuleComponent* RangeAttackCollision;
};
