// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MainGame/StageManager.h"
#include "MainGame/PlayerManager.h"
#include "YggGameState.generated.h"

class UClass;

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AYggGameState(const FObjectInitializer& ObjectInitializer);


protected:
	void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	AStageManager* GetStageManager() const;

	UFUNCTION(BlueprintCallable)
	APlayerManager* GetPlayerManager() const;

	UFUNCTION(BlueprintCallable)
	void InitPlayerManager();

	UFUNCTION(BlueprintCallable)
	void InitStageManager(TSubclassOf<AStageManager> _Test);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UClass* PlayerManagerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UClass* StageManagerClass;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	APlayerManager* PlayerManager;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	AStageManager* StageManager;
};
