// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "YggPlayerController.generated.h"

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AYggPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SetGenericTeamId(const FGenericTeamId& _TeamID) override;

	FGenericTeamId GetGenericTeamId() const override;

protected:
	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	FGenericTeamId TeamID;
};
