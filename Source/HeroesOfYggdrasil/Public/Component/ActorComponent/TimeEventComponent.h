// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimeEventComponent.generated.h"




USTRUCT()
struct HEROESOFYGGDRASIL_API FTimeEvent
{
	GENERATED_BODY()

public:
	bool bIsStarted = false;
	bool bIsLoop = false;
	TFunction<void()> StartFunction = nullptr;
	TFunction<void(float, float)> UpdateFunction = nullptr;
	TFunction<void()> EndFunction = nullptr;
	float StartTimer = 0.0f;
	float CurTime = 0.0f;
	float LoopTimer = 0.0f;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROESOFYGGDRASIL_API UTimeEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTimeEventComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	

	void AddEvent(float StartTimer, float LoopTimer, TFunction<void(float, float)>UpdateFunction, bool IsLoop, TFunction<void()> StartFunction = nullptr, TFunction<void()> EndFunction = nullptr);
	void AddStartEvent(float StartTimer, TFunction<void()> StartFunction);

private:
	TArray<FTimeEvent> Events;

};
