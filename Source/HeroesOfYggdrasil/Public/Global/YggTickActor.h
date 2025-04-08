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



UENUM(BlueprintType)
enum class EStatusEffectType : uint8
{
	Poison    UMETA(DisplayName = "Poison"),
	Burn      UMETA(DisplayName = "Burn"),
	Slow	  UMETA(DisplayName = "Slow"),
	Stunned   UMETA(DisplayName = "Stunned")
};




UCLASS()
class HEROESOFYGGDRASIL_API AYggTickActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYggTickActor();

	UFUNCTION()
	void InitTickActor(EStatusEffectType StatusEffect);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTickDamage(class AYggCharacter* _Target, float _Interval, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Tag")
	void DestroyStatusTag();

	UFUNCTION(BlueprintCallable, Category = "Tag")
	void CheckStatusTag();

	UFUNCTION(BlueprintCallable, Category = "Component")
	void DisableAllComponents();

	static AYggTickActor* SpawnTickEffectIfNotExist(
		UObject* WorldContext,
		AYggCharacter* Target,
		TSubclassOf<AYggTickActor> TickActorClass,
		EStatusEffectType EffectType,
		float TickInterval,
		float DamagePerTick
	);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickDataTable")
	UDataTable* StatusTickDataTable;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TickDataTable")
	FName StatusRowName = TEXT("None");

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

	UPROPERTY(VisibleAnywhere, Category = "Tick")
	UTimeEventComponent* TimeEventComponent;

	UPROPERTY(VisibleAnywhere, Category = "Tick")
	FName Tag;
};
