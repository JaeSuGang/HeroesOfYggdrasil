// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "YggCapsuleComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HEROESOFYGGDRASIL_API UYggCapsuleComponent : public UCapsuleComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void CollisionOn();
	UFUNCTION(BlueprintCallable)
	void CollisionOff();
};
