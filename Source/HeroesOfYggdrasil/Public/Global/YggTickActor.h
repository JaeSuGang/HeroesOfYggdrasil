// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/YggStructData.h"
#include "NiagaraSystem.h"
#include "YggTickActor.generated.h"

class UYggAttackCapsuleComponent;
class UDataTable;
class USceneComponent;
class UParticleSystem;
class UNiagaraSystem;

UCLASS()
class HEROESOFYGGDRASIL_API AYggTickActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYggTickActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UYggAttackCapsuleComponent* GetStatusTickCollision()
	{
		return StatusTickCollision;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickDataTable")
	UDataTable* StatusTickDataTable;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefualtSceneRoot;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickTime")
	float StatusTickTime;

	UPROPERTY(EditAnywhere, Category = "TickEffects")
	TSoftObjectPtr<UParticleSystem> TickParticle;

	UPROPERTY(EditAnywhere, Category = "TickEffects")
	TSoftObjectPtr<UNiagaraSystem> TickNiagaraSystem;

	UPROPERTY(EditAnywhere, Category = "TickCollision")
	UYggAttackCapsuleComponent* StatusTickCollision;
};
