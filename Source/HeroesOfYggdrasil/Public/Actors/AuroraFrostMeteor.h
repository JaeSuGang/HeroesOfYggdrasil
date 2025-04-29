// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuroraFrostMeteor.generated.h"

class UCapsuleComponent;
class UCharacterAttributeComponent;
class AEnemyCharacter;
class AYggHeroAurora;

UCLASS()
class HEROESOFYGGDRASIL_API AAuroraFrostMeteor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuroraFrostMeteor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnMeteorOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMeteorOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SpawnMeteorShower();

	UFUNCTION()
	void DestroyMeteor();

	float DamageLogic(UCharacterAttributeComponent* Attack, UCharacterAttributeComponent* Hit);

	UPROPERTY (VisibleAnywhere)
	USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
	TObjectPtr<UParticleSystem> MeteorShower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particle")
	TObjectPtr<UParticleSystem> MeteorPortal;

	FTimerHandle MeteorTimerHandle;

	FTimerHandle DestroyTimerHandle;

	UPROPERTY()
	TMap<AEnemyCharacter*, FTimerHandle> EnemyDamageTimers;

	UFUNCTION()
	void ApplyPeriodicDamage(AEnemyCharacter* Enemy);

	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UCapsuleComponent* MeteorCapsule;

	UPROPERTY()
	float Coefficient;

	UPROPERTY()
	float AttPower;

private:
	TWeakObjectPtr<AYggHeroAurora> CachedOwner;
};
