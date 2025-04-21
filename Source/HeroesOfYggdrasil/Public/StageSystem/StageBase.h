// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StageBase.generated.h"

class UStageSystem;
class UStageDataAsset;

USTRUCT()
struct FOnEnterStageDelegateParams
{
	GENERATED_BODY()

	UPROPERTY()
	int NewRound;
};

USTRUCT()
struct FOnExitStageDelegateParams
{
	GENERATED_BODY()

	UPROPERTY()
	int CurrentRound;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterStageDelegate, FOnEnterStageDelegateParams, OnEnterStageDelegateParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitStageDelegate, FOnExitStageDelegateParams, OnExitStageDelegateParams);

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

	UFUNCTION()
	virtual void Local_OnEnterStage(int NewRound);

	UFUNCTION()
	virtual void Local_OnExitStage(int CurrentRound);

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
	FOnEnterStageDelegate OnEnterStageDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnExitStageDelegate OnExitStageDelegate;

public:
	UPROPERTY(VisibleInstanceOnly)
	UStageSystem* StageSystem;

	UPROPERTY()
	bool bIsUsingTimer;
};
