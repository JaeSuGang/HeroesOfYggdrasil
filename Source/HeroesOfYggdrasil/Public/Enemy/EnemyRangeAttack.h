// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/YggEnumData.h"
#include "Data/YggStructData.h"
#include "Player/YggHero.h"
#include "EnemyRangeAttack.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AEnemyRangeAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyRangeAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UProjectileMovementComponent* GetProjectileMovement()
	{
		return ProjectileMovement;
	}

	UFUNCTION()
	void InitializeRangeAttack();

	UFUNCTION()
	FName GetMeshNameByKey(const FString& _DataString);

	UFUNCTION()
	void OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefualtSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Poison", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ObjectMesh;

	UPROPERTY(EditAnywhere)
	UDataTable* EnemyProjectileData;

	UPROPERTY(EditAnywhere, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Poison", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereObjectCollision;

	UPROPERTY(EditAnywhere)
	float DestroyTime;
};
