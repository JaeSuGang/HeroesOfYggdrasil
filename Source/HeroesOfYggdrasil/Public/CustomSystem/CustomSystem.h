// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/AssetManager.h"
#include "UpgradeSystem/UpgradeDataAsset.h"
#include "CustomSystem.generated.h"


UCLASS(NotBlueprintable,
	meta = (RestrictedToClassess = "AGameState", BlueprintSpawnableComponent),
	HideCategories = (Variable, Tags, ComponentTick, ComponentReplication, Activation, Cooking, AssetUserData, Replication))
class HEROESOFYGGDRASIL_API UCustomSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UCustomSystem();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION()
	virtual void RegisterObjectsToReplicate();

	UFUNCTION()
	virtual void UnregisterObjectsToReplicate();
	
public:
	template <typename T>
	T* GetDataAssetFromPrimaryAssetId(FPrimaryAssetId PrimaryDataAssetId)
	{
		TSharedPtr<FStreamableHandle> Handle = GEngine->AssetManager->LoadPrimaryAsset(PrimaryDataAssetId);
		if (Handle.IsValid())
		{
			Handle->WaitUntilComplete();

			T* LoadedDataAsset = GEngine->AssetManager->GetPrimaryAssetObject<T>(PrimaryDataAssetId);
			return LoadedDataAsset;
		}
		return nullptr;
	}
};
