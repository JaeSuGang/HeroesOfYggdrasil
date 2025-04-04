// Coded By AssortRock Unreal Engine Class Project


#include "Upgrade/UpgradeManager.h"

#include "Engine/AssetManager.h"
#include "Algo/RandomShuffle.h"

#include "MainGame/MainGameState.h"
#include "Upgrade/UpgradeDataAsset.h"
#include "Upgrade/UpgradeEffectBase.h"
#include "Upgrade/UpgradeEffects.h"
#include "Attribute/HeroAttributeComponent.h"
#include "MainGame/MainGamePlayerState.h"

AUpgradeManager::AUpgradeManager()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
}

AUpgradeManager* AUpgradeManager::Get(UObject* WorldContextObject)
{
	return WorldContextObject->GetWorld()->GetGameStateChecked<AMainGameState>()->UpgradeManager;
}

void AUpgradeManager::BeginPlay()
{
	Super::BeginPlay();

	// GEngine->AssetManager
}

bool AUpgradeManager::GetPlayerUpgradeChoicesAsDataAsset(APlayerController* PC, TArray<UUpgradeDataAsset*>& UpgradeChoices) const
{
	if (AMainGamePlayerState* MPS = PC->GetPlayerState<AMainGamePlayerState>())
	{
		TSharedPtr<FStreamableHandle> Handle = GEngine->AssetManager->LoadPrimaryAssets(MPS->AvailableUpgradeIds);
		if (Handle.IsValid())
		{
			Handle->WaitUntilComplete();

			for (FPrimaryAssetId& AssetId : MPS->AvailableUpgradeIds)
			{
				if (UUpgradeDataAsset* UpgradeDataAsset = GEngine->AssetManager->GetPrimaryAssetObject<UUpgradeDataAsset>(AssetId))
				{
					UpgradeChoices.Add(UpgradeDataAsset);
				}
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	return false;
}

void AUpgradeManager::Upgrade(UHeroAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData)
{
	if (HasAuthority())
	{
		UpgradeInternal(AttributeComponent, UpgradeData);
	}
	else
	{
		RequestUpgrade(AttributeComponent->GetOwner(), UpgradeData->GetPrimaryAssetId());
	}
}

void AUpgradeManager::RequestUpgrade_Implementation(AActor* AttributeOwner, FPrimaryAssetId AssetId)
{
	UHeroAttributeComponent* HAC = AttributeOwner->GetComponentByClass<UHeroAttributeComponent>();
	
	GEngine->AssetManager->LoadPrimaryAsset(AssetId, TArray<FName>(), FStreamableDelegate::CreateLambda([this, HAC, AssetId]()
		{
			if (UObject* LoadedObject = GEngine->AssetManager->GetPrimaryAssetObject(AssetId))
			{
				if (UUpgradeDataAsset* UpgradeDataAsset = Cast<UUpgradeDataAsset>(LoadedObject))
				{
					UpgradeInternal(HAC, UpgradeDataAsset);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("%S%u : Cast Failed"), __FUNCTION__, __LINE__);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("%S%u : Invalid Asset"), __FUNCTION__, __LINE__);
			}

			
		}));

}

void AUpgradeManager::UpgradeInternal(UHeroAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData)
{
	if (!AttributeComponent || !UpgradeData)
		return;

	for (UUpgradeEffectBase* EffectBase : UpgradeData->UpgradeEffects)
	{
		if (UUpgradeEffect_Stats* Effect = Cast<UUpgradeEffect_Stats>(EffectBase))
		{
			Effect->Apply(AttributeComponent);
		}
		if (UUpgradeEffect_TeamStats* Effect = Cast<UUpgradeEffect_TeamStats>(EffectBase))
		{
			Effect->Apply();
		}
	}
}

void AUpgradeManager::GenerateUpgradeChoices(APlayerController* PC, int ChoiceCount)
{
	if (HasAuthority())
	{
		GenerateUpgradeChoicesInternal(PC, ChoiceCount);
	}
	else
	{
		RequestGenerateUpgradeChoices(PC, ChoiceCount);
	}
}

void AUpgradeManager::RequestGenerateUpgradeChoices_Implementation(APlayerController* PC, int ChoiceCount)
{
	GenerateUpgradeChoicesInternal(PC, ChoiceCount);
}

void AUpgradeManager::GenerateUpgradeChoicesInternal(APlayerController* PC, int ChoiceCount)
{
	if (AMainGamePlayerState* MPS = PC->GetPlayerState<AMainGamePlayerState>())
	{
		MPS->AvailableUpgradeIds.Empty();

		TArray<FPrimaryAssetId> TotalUpgradeIds;
		if (GEngine->AssetManager->GetPrimaryAssetIdList(TEXT("Upgrade"), TotalUpgradeIds))
		{
			/* 랜덤 산출 */
			TArray<int> RandomOrder{};
			for (int i = 0; i < TotalUpgradeIds.Num(); ++i)
			{
				RandomOrder.Add(i);
			}

			/* UpgradeIds에 산출된 랜덤 어레이의 앞에서부터 삽입 */
			for (int i = 0; i < ChoiceCount; ++i)
			{
				MPS->AvailableUpgradeIds.Push(TotalUpgradeIds[RandomOrder.Pop()]);
			}
			
		}
	}
}
