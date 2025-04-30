// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggAbilityUserWidget.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MainGame/MainGamePlayerState.h"

#include "UpgradeSystem/UpgradeSystem.h"
#include "UpgradeSystem/UpgradeDataAsset.h"
#include "Attribute/HeroAttributeComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

void UYggAbilityUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectButton = Cast<UButton>(GetWidgetFromName(TEXT("SelectButton")));

	APlayerController* PC = GetOwningPlayer();

	AMainGameHUD* MainGameHUD = Cast<AMainGameHUD>(PC->GetHUD());

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(this, &UYggAbilityUserWidget::AbilitySelectEvent);
		SelectButton->OnClicked.AddDynamic(MainGameHUD, &AMainGameHUD::AbilitySelectEvent);
		SelectButton->OnClicked.AddDynamic(this, &UYggAbilityUserWidget::OnClickSound);
		SelectButton->OnHovered.AddDynamic(this, &UYggAbilityUserWidget::PlayHoverAnim);
		SelectButton->OnUnhovered.AddDynamic(this, &UYggAbilityUserWidget::PlayUnHoverAnim);
	}
}

void UYggAbilityUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	APlayerController* PC = GetOwningPlayer();

	if (IsValid(PC))
	{
		AMainGameHUD* MainGameHUD = Cast<AMainGameHUD>(PC->GetHUD());

		if (SelectButton)
		{
			SelectButton->OnClicked.RemoveDynamic(this, &UYggAbilityUserWidget::AbilitySelectEvent);
			SelectButton->OnClicked.RemoveDynamic(MainGameHUD, &AMainGameHUD::AbilitySelectEvent);
			SelectButton->OnClicked.RemoveDynamic(this, &UYggAbilityUserWidget::OnClickSound);
			SelectButton->OnHovered.RemoveDynamic(this, &UYggAbilityUserWidget::PlayHoverAnim);
			SelectButton->OnUnhovered.RemoveDynamic(this, &UYggAbilityUserWidget::PlayUnHoverAnim);
		}
	}
}

FSlateBrush UYggAbilityUserWidget::MakeBrush(UTexture2D* Tex, FVector2D Size)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Tex);
	Brush.ImageSize = Size;
	Brush.DrawAs = ESlateBrushDrawType::Image;
	return Brush;
}

void UYggAbilityUserWidget::AbilityInit(FPrimaryAssetId& AssetId)
{
	FVector2D Size(80.0f, 80.0f);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMainGamePlayerState* PS = PC->GetPlayerState<AMainGamePlayerState>();

	UUpgradeSystem* UpgradeSystem = UUpgradeSystem::Get(GetWorld());

	UpgradeDataAsset = UpgradeSystem->GetDataAssetFromPrimaryAssetId<UUpgradeDataAsset>(AssetId);

	if (IsValid(UpgradeDataAsset))
	{
		AbilityImage->SetBrush(MakeBrush(UpgradeDataAsset->UpgradeImage, Size));
		AbilityName->SetText(FText::FromName(UpgradeDataAsset->UpgradeName));
		AbilityInfo->SetText(FText::FromName(UpgradeDataAsset->UpgradeDescription));
		ApplyRarityEffect(UpgradeDataAsset->Rarity);
		AbilityInfo->SetAutoWrapText(true);
	}
}

void UYggAbilityUserWidget::AbilitySelectEvent()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	UHeroAttributeComponent* CAC = PC->GetPawn()->GetComponentByClass<UHeroAttributeComponent>();
	
	UUpgradeSystem* UpgradeSystem = UUpgradeSystem::Get(GetWorld());
		
	if (AMainGameHUD* HUD = PC->GetHUD<AMainGameHUD>())
	{
		HUD->AddAbility(UpgradeDataAsset->UpgradeName, UpgradeDataAsset->UpgradeImage, UpgradeDataAsset->UpgradeDescription);
	}

	UpgradeSystem->Upgrade(CAC, UpgradeDataAsset);
}

void UYggAbilityUserWidget::ApplyRarityEffect(EUpgradeRarity Rarity)
{
	UMaterialInstanceDynamic* EdgeMat = UMaterialInstanceDynamic::Create(EdgeMaterial, this);

	switch (Rarity)
	{
	case EUpgradeRarity::Common:
		EdgeMat->SetVectorParameterValue("Color1", FLinearColor(1.0f, 1.0f, 1.0f));
		Edge->SetBrushFromMaterial(EdgeMat);
		break;
	case EUpgradeRarity::Epic:
		EdgeMat->SetVectorParameterValue("Color1", FLinearColor(0.27451f, 0.14902f, 0.47451f));
		Edge->SetBrushFromMaterial(EdgeMat);
		break;
	case EUpgradeRarity::Legendary:
		EdgeMat->SetVectorParameterValue("Color1", FLinearColor(1.0f, 0.843137f, 0.0f));
		Edge->SetBrushFromMaterial(EdgeMat);
		break;
	default:
		break;
	}
}

void UYggAbilityUserWidget::PlayHoverAnim()
{
	PlayAnimation(HoverAnim);
}

void UYggAbilityUserWidget::PlayUnHoverAnim()
{
	PlayAnimationReverse(HoverAnim);
}

void UYggAbilityUserWidget::OnClickSound()
{
	if (ClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound);
	}
}
