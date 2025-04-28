// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuroraFrostCatalyst.generated.h"

class UCapsuleComponent;
class AAuroraFrostMeteor;
class UProjectileMovementComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AAuroraFrostCatalyst : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuroraFrostCatalyst();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCatalystHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CatalystCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aurora")
	TSubclassOf<AAuroraFrostMeteor> MeteorClass;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* ProjectileMovement;
};
