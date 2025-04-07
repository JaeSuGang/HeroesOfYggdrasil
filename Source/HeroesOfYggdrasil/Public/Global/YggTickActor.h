// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/YggStructData.h"
#include "NiagaraSystem.h"
#include "YggTickActor.generated.h"

class UDataTable;
class USceneComponent;
class UParticleSystem;
class UNiagaraSystem;
class UTickDamageComponent;


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

	void SetTickDamage(class AYggCharacter* _Target, float _Interval, float DamageAmount);


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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tick")
	UTickDamageComponent* TickDamageComponent;

};
