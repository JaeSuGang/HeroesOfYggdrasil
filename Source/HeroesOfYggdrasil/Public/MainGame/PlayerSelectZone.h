// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggPawn.h"
#include "StageSystem/StageSystem.h"
#include "PlayerSelectZone.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API APlayerSelectZone : public AYggPawn
{
	GENERATED_BODY()
	
public:
	APlayerSelectZone();

protected:
	void Restart() override;
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void PossessedBy(AController* controller) override;
	void EndPlay(EEndPlayReason::Type endReason) override;
	void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	APawn* GetSpawnedSelectable() const;

public:
	UFUNCTION()
	void ForceMainWidget();

	UFUNCTION(Server, Reliable)
	void SetToPosition(int nIndex);

	UFUNCTION(Server, Reliable)
	void SelectCharacter();
	void SelectCharacter_Implementation();

	UFUNCTION(Server, Reliable)
	void SpawnSelectable(int nSpawnableIndex);

	UFUNCTION()
	void SpawnNextSelectable(int nHowMuchNext);

	UFUNCTION()
	void OnStartGame(FOnGameStartParams OnGameStartParams);

public:
	UPROPERTY(EditAnywhere, Category = YGG)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = YGG)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = YGG)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = YGG)
	UDataTable* SelectablesTable;

	UPROPERTY(Replicated, VisibleInstanceOnly, Category = YGG)
	APawn* SpawnedSelectable;

	UPROPERTY(EditAnywhere, Category = YGG)
	FVector ZoneInterval;

	UPROPERTY(EditAnywhere, Category = YGG)
	FVector CameraDistance;

	UPROPERTY(Replicated, VisibleInstanceOnly, Category = YGG)
	int CurrentTableIndex;

	APlayerStart* PlayerStart;
};
