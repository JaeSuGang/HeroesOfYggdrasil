// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TickDamageComponent.generated.h"


class AYggCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROESOFYGGDRASIL_API UTickDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTickDamageComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	AYggCharacter* TargetActor;

	UPROPERTY(EditAnywhere, Category = "Tick")
	float TickInterval;

	UPROPERTY(EditAnywhere, Category = "Tick")
	float DamageAmount;

	UPROPERTY(EditAnywhere, Category = "Tick")
	float ElapsedTime;


protected:
	FTimerHandle TickTimerHandle;

	UFUNCTION()
	void ApplyDamage();
};
