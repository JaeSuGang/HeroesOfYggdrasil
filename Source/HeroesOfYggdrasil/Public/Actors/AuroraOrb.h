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

	UPROPERTY()
	float MoveSpeed = 500.0f;

	float AttPower;
};
