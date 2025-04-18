// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuroraOrb.generated.h"

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

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> PSTemplate;

private:
	FVector MoveDirection = FVector::ZeroVector;

	UPROPERTY()
	float MoveSpeed = 500.0f;
};
