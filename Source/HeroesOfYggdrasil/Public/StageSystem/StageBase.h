// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StageBase.generated.h"

class UStageSystem;
class UStageDataAsset;

USTRUCT()
struct FOnEnterStageParams
{
	GENERATED_BODY()

	UPROPERTY()
	int PrevRound;

	UPROPERTY()
	int NewRound;
};

USTRUCT()
struct FOnExitStageParams
{
	GENERATED_BODY()

	UPROPERTY()
	int PrevRound;

	UPROPERTY()
	int NewRound;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterStageInternal, FOnEnterStageParams, OnEnterStageParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitStageInternal, FOnExitStageParams, OnExitStageParams);

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
	UFUNCTION()
	virtual void BeginPlay(UStageSystem* NewStageSystem);

	UFUNCTION()
	virtual void TickLogic(float fDeltaTime);

public:
	UFUNCTION()
	void EnterNextStage();

	UFUNCTION()
	void SetTimer(float fTime);

	UFUNCTION()
	float GetTimer() const;

public:
	/* Replicated 되지 않음.
	* 서버가 Bind할 시 서버 로직에 영향
	* 클라이언트가 Bind할 시 자기 클라이언트에 영향
	*/
	UPROPERTY(BlueprintAssignable)
	FOnEnterStageInternal OnEnterStageInternal;

	UPROPERTY(BlueprintAssignable)
	FOnExitStageInternal OnExitStageInternal;

public:
	UPROPERTY(VisibleInstanceOnly)
	UStageSystem* StageSystem;

	UPROPERTY()
	int Round;

	UPROPERTY()
	bool bIsUsingTimer;
};
