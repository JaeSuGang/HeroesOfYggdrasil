// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YggProjectileActor.generated.h"


UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	Line UMETA(DisplayName = "Line"),
	Parabola UMETA(DisplayName = "Parabola"),
};

UCLASS()
class HEROESOFYGGDRASIL_API AYggProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYggProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	EProjectileType ProjectileType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float DeathTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Height;

	UPROPERTY()
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY()
	TObjectPtr<AActor> TargetActor;

	FVector TargetLocation;

	FTimerHandle DeathTimerHandle;

};
