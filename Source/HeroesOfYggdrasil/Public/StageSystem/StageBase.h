// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StageBase.generated.h"

class UStageDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnterStageInternal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExitStageInternal);

/**
 * 담당 코더 : 김경민
 */
UCLASS(EditInlineNew)
class HEROESOFYGGDRASIL_API UStageBase : public UObject
{
	GENERATED_BODY()
	
public:
	UStageBase();

public:
	virtual bool IsSupportedForNetworking() const override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnEnterStageInternal OnEnterStageInternal;

	UPROPERTY(BlueprintAssignable)
	FOnExitStageInternal OnExitStageInternal;

public:
	UPROPERTY()
	int Round;
};
