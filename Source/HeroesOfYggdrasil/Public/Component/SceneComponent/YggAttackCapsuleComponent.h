// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Component/SceneComponent/YggCapsuleComponent.h"
#include "YggAttackCapsuleComponent.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggAttackCapsuleComponent : public UYggCapsuleComponent
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;
	
};
