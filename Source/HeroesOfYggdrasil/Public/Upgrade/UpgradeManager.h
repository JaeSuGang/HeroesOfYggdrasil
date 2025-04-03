// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "UpgradeManager.generated.h"

class UUpgradeDataAsset;
class UAttributeComponent;

/**
 * 담당 코더 : 김경민
 */
UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API AUpgradeManager : public AInfo
{
	GENERATED_BODY()
	
public:
	AUpgradeManager();

	UFUNCTION(BlueprintCallable)
	static AUpgradeManager* Get(UWorld* WorldContext);

	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void Upgrade(UAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData);

public:
	UPROPERTY()
	TObjectPtr<UDataTable> UpgradeTable;

};
