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
	TargetParabola UMETA(DisplayName = "TargetParabola"),
	Homing UMETA(DisplayName = "Homing"),
};

USTRUCT(BlueprintType)
struct FSpawnProjectileDataRow : public FTableRowBase
{
	GENERATED_BODY()
	FSpawnProjectileDataRow() {}
	~FSpawnProjectileDataRow() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileData")
	EProjectileType ProjectileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileData")
	float DestroyTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileData")
	float Height;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileData")
	float InitialSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileData")
	float MaxSpeed;
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

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void SetAimDir(FVector _AimDirection);

	UFUNCTION(Reliable, Server)
	void Server_SetAimDir(FVector _AimDirection);

	UFUNCTION(Reliable, NetMulticast)
	void MultiCast_SetAimDir(FVector _AimDirection);


	UFUNCTION()
	void SetOwnerCharacter(class AYggCharacter* _OwnerCharacter) { OwnerCharacter = _OwnerCharacter; }

	UFUNCTION()
	void SetTargetLocation(FVector _TargetLocation) { TargetLocation = _TargetLocation; }
	UFUNCTION(BlueprintCallable)
	void SetHomingTarget(AActor* Target);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggProjectileActor")
	EProjectileType ProjectileType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AYggProjectileActor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AYggProjectileActor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UYggAttackCapsuleComponent> AttackCapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggProjectileActor")
	UDataTable* ProjectileData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggProjectileActor")
	FName RowName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AYggProjectileActor")
	class AYggCharacter* OwnerCharacter;
	
	
	FVector TargetLocation;

	UPROPERTY(Replicated)
	TWeakObjectPtr<AActor> HomingTargetActor;

	FSpawnProjectileDataRow ProjectileDataRow;

	UPROPERTY(Replicated)
	FVector AimDirection;


	void LineMode();
	void ParabolaMode();
	void TargetParabolaMode();
	void HomingMode();

};
