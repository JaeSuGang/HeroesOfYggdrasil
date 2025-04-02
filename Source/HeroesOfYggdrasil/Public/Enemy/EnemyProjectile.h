// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/YggEnumData.h"
#include "Data/YggStructData.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyProjectile();

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
protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefualtSceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Arrow", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ArrowMesh;

	UPROPERTY(EditAnywhere)
	UDataTable* EnemyProjectileData;

	UPROPERTY(EditAnywhere, Category = Movement)
	class UProjectileMovementComponent* ProjectileMovement;
};
