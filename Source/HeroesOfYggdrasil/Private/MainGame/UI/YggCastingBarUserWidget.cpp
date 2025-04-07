// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggCastingBarUserWidget.h"

#include "Player/YggHero.h"

#include "Attribute/HeroAttributeComponent.h"
#include "Components/ProgressBar.h"

#include "Kismet/GameplayStatics.h"

void UYggCastingBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SetVisibility(ESlateVisibility::Collapsed);
}

void UYggCastingBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (bAreDelegatesBound) return;

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Pawn) return;

	AYggHero* Hero = Cast<AYggHero>(Pawn);
	if (!IsValid(Hero) || !Hero->IsLocallyControlled()) return;

	Hero->OnSkillCast.RemoveDynamic(this, &UYggCastingBarUserWidget::StartCasting);
	Hero->OnSkillCastEnd.RemoveDynamic(this, &UYggCastingBarUserWidget::EndCasting);

	Hero->OnSkillCast.AddDynamic(this, &UYggCastingBarUserWidget::StartCasting);
	Hero->OnSkillCastEnd.AddDynamic(this, &UYggCastingBarUserWidget::EndCasting);

	bAreDelegatesBound = true;
}

void UYggCastingBarUserWidget::NativeDestruct()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Pawn)
	{
		AYggHero* Hero = Cast<AYggHero>(Pawn);
		if (Hero)
		{
			Hero->OnSkillCast.RemoveDynamic(this, &UYggCastingBarUserWidget::StartCasting);
			Hero->OnSkillCastEnd.RemoveDynamic(this, &UYggCastingBarUserWidget::EndCasting);
		}
	}

	Super::NativeDestruct();
}

void UYggCastingBarUserWidget::StartCasting(float Duration)
{
	CastingTime = Duration;
	RemainingTime = Duration;

	if (CastingBar)
	{
		CastingBar->SetPercent(1.0f);
		SetVisibility(ESlateVisibility::Visible);
	}

	GetWorld()->GetTimerManager().SetTimer(CastingTimerHandle, this, &UYggCastingBarUserWidget::UpdateCastingBar, 0.05f, true);
}

void UYggCastingBarUserWidget::UpdateCastingBar()
{
	RemainingTime -= 0.05f;

	if (RemainingTime <= 0.0f)
	{
		EndCasting();
		return;
	}

	float Progress = RemainingTime / CastingTime;
	if (CastingBar)
	{
		CastingBar->SetPercent(Progress);
	}
}

void UYggCastingBarUserWidget::EndCasting()
{
	GetWorld()->GetTimerManager().ClearTimer(CastingTimerHandle);

	SetVisibility(ESlateVisibility::Collapsed);
}