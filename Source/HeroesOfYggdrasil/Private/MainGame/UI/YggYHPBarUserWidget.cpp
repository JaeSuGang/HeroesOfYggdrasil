// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggYHPBarUserWidget.h"

#include "MainGame/UI/MainGameHUD.h"
#include "NPC/Yggdrasil.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UYggYHPBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AMainGameHUD* HUD = PC->GetHUD<AMainGameHUD>();
	
	Yggdrasil = HUD->GetYggdrasil();
}

void UYggYHPBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CAC = Yggdrasil->GetAttributeComponent();

	CAC->ClientDelegate_OnStatusChanged.AddDynamic(this, &UYggYHPBarUserWidget::UpdateHPBar);

	UpdateHPBar();
}

void UYggYHPBarUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UYggYHPBarUserWidget::UpdateHPBar()
{
	if (IsValid(HPBar) && IsValid(Health))
	{
		FText HealthText = FText::Format(FText::FromString("{0} / {1}"), FText::AsNumber(CAC->HP), FText::AsNumber(CAC->MaxHP));

		HPBar->SetPercent(CAC->HP / CAC->MaxHP);
		Health->SetText(HealthText);
	}
}