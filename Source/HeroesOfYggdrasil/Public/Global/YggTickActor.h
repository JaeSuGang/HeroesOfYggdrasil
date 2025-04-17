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
class UTimeEventComponent;
class AYggHero;
struct FStatusTickDataRow;



UCLASS()
class HEROESOFYGGDRASIL_API AYggTickActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYggTickActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	void TickEffectInit();

	UFUNCTION(NetMulticast, Reliable)
	virtual void SpawnEffect(AYggCharacter* _Target);

	UFUNCTION(NetMulticast, Reliable)
	virtual void CleanupEffects();


	UFUNCTION()
	void OnRep_EffectAssets();

	UFUNCTION(BlueprintCallable, Category = "Tag")
	void DestroyStatusTag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickDataTable")
	UDataTable* StatusTickDataTable;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickDataTable")
	FName StatusRowName = TEXT("Poison");


	UPROPERTY(Replicated, VisibleAnywhere)
	USceneComponent* DefualtSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickTime")
	float StatusTickTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickTime")
	float TickActorScale;

	UPROPERTY(EditAnywhere, Replicated, ReplicatedUsing = OnRep_EffectAssets, BlueprintReadWrite, Category = "TickEffect")
	TSoftObjectPtr<UNiagaraSystem> NiagaraEffect;

	UPROPERTY(EditAnywhere, Replicated, ReplicatedUsing = OnRep_EffectAssets, BlueprintReadWrite, Category = "TickEffect")
	TSoftObjectPtr<UParticleSystem> ParticleEffect;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "TickEffects")
	EStatusEffectType TickEffectType;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "Tick")
	UTickDamageComponent* TickDamageComponent;

	UPROPERTY(VisibleAnywhere, Category = "Tick")
	UTimeEventComponent* TimeEventComponent;

	UPROPERTY(VisibleAnywhere, Category = "Tick")
	FName Tag;

	
};
