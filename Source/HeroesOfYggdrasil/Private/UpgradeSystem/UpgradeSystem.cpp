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

void UUpgradeSystem::AddUpgradePointInternal(APlayerState* PlayerState, int PointToAdd)
{
	if (GetOwner()->HasAuthority())
	{
		if (AMainGamePlayerState* MPS = Cast<AMainGamePlayerState>(PlayerState))
		{
			SetUpgradePointInternal(PlayerState, MPS->UpgradePoints + PointToAdd);
		}
	}
}

void UUpgradeSystem::SetUpgradePointInternal(APlayerState* PlayerState, int PointToSet)
{
	if (GetOwner()->HasAuthority())
	{
		if (AMainGamePlayerState* MPS = Cast<AMainGamePlayerState>(PlayerState))
		{
			MPS->UpgradePoints = PointToSet;
			MPS->OnRep_UpgradePoints();
			GenerateUpgradeChoicesInternal(MPS, 3);
		}
	}
}

void UUpgradeSystem::UpgradeByUpgradeId(UAttributeComponent* AttributeComponent, FPrimaryAssetId UpgradeDataAssetId)
{
	if (GetOwner()->HasAuthority())
	{
		GEngine->AssetManager->LoadPrimaryAsset(UpgradeDataAssetId, TArray<FName>(), FStreamableDelegate::CreateLambda([this, AttributeComponent, UpgradeDataAssetId]()
			{
				if (UObject* LoadedObject = GEngine->AssetManager->GetPrimaryAssetObject(UpgradeDataAssetId))
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
	else
	{
		RequestUpgrade(AttributeComponent, UpgradeDataAssetId);
	}
}

void UUpgradeSystem::Upgrade(UAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData)
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

void UUpgradeSystem::RequestUpgrade_Implementation(UAttributeComponent* AttributeComponent, FPrimaryAssetId AssetId)
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

void UUpgradeSystem::UpgradeInternal(UAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData)
{
	if (!AttributeComponent || !UpgradeData)
		return;

	for (UUpgradeEffectBase* EffectBase : UpgradeData->UpgradeEffects)
	{
		EffectBase->ApplyInternal(AttributeComponent);
	}

	if (APawn* OwnerPawn = Cast<APawn>(AttributeComponent->GetOwner()))
	{
		if (AMainGamePlayerState* MPS = OwnerPawn->GetPlayerState<AMainGamePlayerState>())
		{
			AddUpgradePointInternal(MPS, -1);
			GenerateUpgradeChoicesInternal(MPS, 3);
		}
	}
}

void UUpgradeSystem::GenerateUpgradeChoices(APlayerState* PS, int ChoiceCount)
{
	if (GetOwner()->HasAuthority())
	{
		GenerateUpgradeChoicesInternal(PS, ChoiceCount);
	}
	else
	{
		RequestGenerateUpgradeChoices(PS, ChoiceCount);
	}
}

void UUpgradeSystem::RequestGenerateUpgradeChoices_Implementation(APlayerState* PS, int ChoiceCount)
{
	GenerateUpgradeChoicesInternal(PS, ChoiceCount);
}

void UUpgradeSystem::GenerateUpgradeChoicesInternal(APlayerState* PS, int ChoiceCount)
{
	if (AMainGamePlayerState* MPS = Cast<AMainGamePlayerState>(PS))
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
