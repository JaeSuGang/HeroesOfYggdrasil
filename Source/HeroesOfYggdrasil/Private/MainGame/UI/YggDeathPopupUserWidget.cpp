// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggDeathPopupUserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

void UYggDeathPopupUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();


}

void UYggDeathPopupUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Pawn) return;

	AYggHero* Hero = Cast<AYggHero>(Pawn);
	if (!IsValid(Hero) || !Hero->IsLocallyControlled()) return;

	Hero->OnRespawn.RemoveDynamic(this, &UYggDeathPopupUserWidget::StartRespawn);

	Hero->OnRespawn.AddDynamic(this, &UYggDeathPopupUserWidget::StartRespawn);

	SetVisibility(ESlateVisibility::Hidden);
}

void UYggDeathPopupUserWidget::StartRespawn(float Duration)
{
	this->SetVisibility(ESlateVisibility::Visible);

	RespawnTime = Duration;
	RemainingTime = Duration;

	FNumberFormattingOptions FormatOptions;
	FormatOptions.MinimumFractionalDigits = 1;
	FormatOptions.MaximumFractionalDigits = 1;
	CountBlock->SetText(FText::AsNumber(RemainingTime, &FormatOptions));

	if (RespawnBar)
	{
		RespawnBar->SetPercent(1.0f);
	}

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UYggDeathPopupUserWidget::UpdateRespawnBar, 0.05f, true);
}

void UYggDeathPopupUserWidget::UpdateRespawnBar()
{
	RemainingTime -= 0.05f;

	FNumberFormattingOptions FormatOptions;
	FormatOptions.MinimumFractionalDigits = 1;
	FormatOptions.MaximumFractionalDigits = 1;
	CountBlock->SetText(FText::AsNumber(RemainingTime, &FormatOptions));

	if (RemainingTime <= 0.0f)
	{
		EndRespawn();
		return;
	}

	float Progress = RemainingTime / RespawnTime;
	if (RespawnBar)
	{
		RespawnBar->SetPercent(Progress);
	}
}

void UYggDeathPopupUserWidget::EndRespawn()
{
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

	this->SetVisibility(ESlateVisibility::Hidden);
}