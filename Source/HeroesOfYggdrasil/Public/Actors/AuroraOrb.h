// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuroraOrb.generated.h"

class UCapsuleComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AAuroraOrb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuroraOrb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOrbOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void SetAttPower(float Value)
	{
		AttPower = Value;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UCapsuleComponent* OrbCapsule;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Particle")
	TObjectPtr<UParticleSystem> PSTrail;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Particle")
	TObjectPtr<UParticleSystem> PSImpact;

private:
	FVector MoveDirection = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category = "Orb")
	FVector TargetPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Orb")
	float MoveSpeed = 1500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Orb")
	float MaxTraceDistance = 10000.f; // Line Trace 최대 거리

	UPROPERTY(EditDefaultsOnly, Category = "Orb")
	float FallbackDistance = 5000.f;  // 충돌 없을 시 사용할 거리

	float AttPower;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Orb|Homing")
	float HomingRadius = 300.f;    // 적 탐지 반경

	UPROPERTY(EditDefaultsOnly, Category = "Orb|Homing")
	float HomingStrength = 0.5f;     // 유도 강도 (클수록 빠름)

	UPROPERTY(EditDefaultsOnly, Category = "Orb|Homing")
	float HomingStartDelay = 0.5f;  // 유도 시작 전 초기 직진 시간

	UPROPERTY(EditDefaultsOnly, Category = "Orb|Homing")
	TEnumAsByte<ECollisionChannel> EnemyObjectType = ECC_GameTraceChannel1;

	float LastHomingDistance;

private:
	FTimerHandle OrbTimer;
	FTimerHandle HomingTimer;

	bool bCanHoming = false;
	AActor* TargetEnemy = nullptr;
};
