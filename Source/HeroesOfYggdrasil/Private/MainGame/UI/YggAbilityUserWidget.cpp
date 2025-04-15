// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggAbilityUserWidget.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "MainGame/MainGamePlayerState.h"

#include "UpgradeSystem/UpgradeSystem.h"
#include "UpgradeSystem/UpgradeDataAsset.h"

#include "UpgradeSystem/UpgradeDataAsset.h"


void UYggAbilityUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectButton = Cast<UButton>(GetWidgetFromName(TEXT("SelectButton")));

	APlayerController* PC = GetOwningPlayer();

	AMainGameHUD* MainGameHUD = Cast<AMainGameHUD>(PC->GetHUD());

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(MainGameHUD, &AMainGameHUD::AbilitySelectEvent);
	}
}

FSlateBrush MakeBrush(UTexture2D* Tex, FVector2D Size)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Tex);
	Brush.ImageSize = Size;
	Brush.DrawAs = ESlateBrushDrawType::Image;
	return Brush;
}

void UYggAbilityUserWidget::AbilityInit()
{
	FVector2D Size(80.0f, 80.0f);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMainGamePlayerState* PS = PC->GetPlayerState<AMainGamePlayerState>();

	UUpgradeSystem* UpgradeSystem = UUpgradeSystem::Get(GetWorld());

	//UpgradeSystem->Upgrade();

	//PS->AvailableUpgradeIds.Num() > 2;
	for (FPrimaryAssetId& AssetId : PS->AvailableUpgradeIds)
	{
		FPrimaryAssetId{ "Upgrade::1" };
		UUpgradeDataAsset* UpgradeData = UpgradeSystem->GetDataAssetFromPrimaryAssetId<UUpgradeDataAsset>(AssetId);
		UpgradeData->UpgradeImage;
		UpgradeData->UpgradeName;
		UpgradeData->UpgradeDescription;

	}



	//UpgradeDataAsset

	//AbilityImage->SetBrush(MakeBrush(, Size));
}
