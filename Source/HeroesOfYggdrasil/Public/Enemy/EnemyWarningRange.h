// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/YggStructData.h"
#include "EnemyWarningRange.generated.h"


class AYggTickActor;

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
	void ChangeArea();

	UFUNCTION()
	void SpawnEffect();
	
	UFUNCTION()
	void OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void SetCollisionOwnerEnemy(AEnemyCharacter* _Enemy);

	UFUNCTION()
	void HideAllComponents();

	float GetDuration()
	{
		return Duration;
	}

	float GetTimeElapsed()
	{
		return TimeElapsed;
	}

	class UYggAttackCapsuleComponent* GetBugTickCollision()
	{
		return BugTickCollision;
	}
	
public:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PlaneMesh;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* WarningMaterial;

	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	UDataTable* AOEDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	float TimeElapsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	class UCharacterAttributeComponent* EnemyAttributeComponent;

	UPROPERTY(EditAnywhere, Category = "EnemyEffects")
	UParticleSystem* BugBallParticle;  

	UPROPERTY(EditAnywhere, Category = "EnemyEffects")
	class AEnemyCharacter* YggCharacterEnemy;

	UPROPERTY(EditAnywhere, Category = "Tick")
	TSubclassOf<AYggTickActor> TickActorClass;

	UPROPERTY(EditAnywhere, Category = "EnemyCapsuleCollision")
	class UYggAttackCapsuleComponent* BugTickCollision;
};
