// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StageSystem.generated.h"

class UStageBase;

UCLASS(NotBlueprintable)
class HEROESOFYGGDRASIL_API UStageSystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStageSystem();

protected:
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	UPROPERTY(Replicated)
	UStageBase* CurrentStage;
};
