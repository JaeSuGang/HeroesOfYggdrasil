// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggAbilityUserWidget.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

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



	//AbilityImage->SetBrush(MakeBrush(, Size));
}
