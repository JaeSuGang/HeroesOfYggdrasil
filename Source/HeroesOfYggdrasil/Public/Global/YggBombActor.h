// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Global/YggProjectileActor.h"
#include "YggBombActor.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggBombActor : public AYggProjectileActor
{
	GENERATED_BODY()
public:
	AYggBombActor();

	virtual void BeginPlay() override;

	UFUNCTION()
	void ExplosionOn();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AYggProjectileActor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UYggAttackCapsuleComponent> ExplosionAttackCapsuleComponent;


	
};
