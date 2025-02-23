// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggActor.h"
#include "PlayerSelectZone.generated.h"

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API APlayerSelectZone : public AYggActor
{
	GENERATED_BODY()
	
public:
	APlayerSelectZone();

protected:
	//void Tick(float fDeltaTime) override;
	void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable)
	void ServerNextSelectable();

public:
	UPROPERTY(EditAnywhere, Category = YGG)
	UDataTable* SelectablesTable;

	int CurrentTableIndex;

	AActor* SpawnedSelectable;
};
