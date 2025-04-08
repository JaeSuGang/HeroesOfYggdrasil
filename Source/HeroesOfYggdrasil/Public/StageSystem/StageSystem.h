// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomSystem/CustomSystem.h"
#include "StageSystem.generated.h"

class UStageBase;

UCLASS()
class HEROESOFYGGDRASIL_API UStageSystem : public UCustomSystem
{
	GENERATED_BODY()

public:	
	UStageSystem();

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void RegisterObjectsToReplicate() override;

	virtual void UnregisterObjectsToReplicate() override;

public:	
	UPROPERTY(Replicated, Instanced, EditAnywhere)
	TArray<UStageBase*> StageCycle;

	UPROPERTY(Replicated)
	UStageBase* CurrentStage;
};
