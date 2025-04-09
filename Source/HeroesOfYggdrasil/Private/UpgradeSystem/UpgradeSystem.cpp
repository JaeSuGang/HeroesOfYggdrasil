// Coded By AssortRock Unreal Engine Class Project


#include "UpgradeSystem/UpgradeSystem.h"

#include "Engine/AssetManager.h"
#include "Algo/RandomShuffle.h"

#include "MainGame/MainGameState.h"
#include "UpgradeSystem/UpgradeDataAsset.h"
#include "UpgradeSystem/UpgradeEffectBase.h"
#include "UpgradeSystem/UpgradeEffects.h"
#include "Attribute/HeroAttributeComponent.h"
#include "MainGame/MainGamePlayerState.h"

UUpgradeSystem::UUpgradeSystem()
{
	SetIsReplicatedByDefault(true);
}

UUpgradeSystem* UUpgradeSystem::Get(const UObject* WorldContextObject)
{
	return WorldContextObject->GetWorld()->GetGameState()->GetComponentByClass<UUpgradeSystem>();
}

void UUpgradeSystem::BeginPlay()
{
	Super::BeginPlay();

	// GEngine->AssetManager
}

bool UUpgradeSystem::GetPlayerUpgradeChoicesAsDataAsset(APlayerController* PC, TArray<UUpgradeDataAsset*>& UpgradeChoices) const
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

void UUpgradeSystem::Upgrade(UHeroAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData)
{
	
	if (GetOwner()->HasAuthority())
	{
		UpgradeInternal(AttributeComponent, UpgradeData);
	}
	else
	{
		RequestUpgrade(AttributeComponent, UpgradeData->GetPrimaryAssetId());
	}
}

void UUpgradeSystem::RequestUpgrade_Implementation(UHeroAttributeComponent* AttributeComponent, FPrimaryAssetId AssetId)
{
	GEngine->AssetManager->LoadPrimaryAsset(AssetId, TArray<FName>(), FStreamableDelegate::CreateLambda([this, AttributeComponent, AssetId]()
		{
			if (UObject* LoadedObject = GEngine->AssetManager->GetPrimaryAssetObject(AssetId))
			{
				if (UUpgradeDataAsset* UpgradeDataAsset = Cast<UUpgradeDataAsset>(LoadedObject))
				{
					UpgradeInternal(AttributeComponent, UpgradeDataAsset);
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

void UUpgradeSystem::UpgradeInternal(UHeroAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData)
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

void UUpgradeSystem::GenerateUpgradeChoices(APlayerController* PC, int ChoiceCount)
{
	if (GetOwner()->HasAuthority())
	{
		GenerateUpgradeChoicesInternal(PC, ChoiceCount);
	}
	else
	{
		RequestGenerateUpgradeChoices(PC, ChoiceCount);
	}
}

void UUpgradeSystem::RequestGenerateUpgradeChoices_Implementation(APlayerController* PC, int ChoiceCount)
{
	GenerateUpgradeChoicesInternal(PC, ChoiceCount);
}

void UUpgradeSystem::GenerateUpgradeChoicesInternal(APlayerController* PC, int ChoiceCount)
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
			Algo::RandomShuffle(RandomOrder);

			/* UpgradeIds에 산출된 랜덤 어레이의 앞에서부터 삽입 */
			for (int i = 0; i < ChoiceCount; ++i)
			{
				MPS->AvailableUpgradeIds.Push(TotalUpgradeIds[RandomOrder.Pop()]);
			}

		}
	}
}
