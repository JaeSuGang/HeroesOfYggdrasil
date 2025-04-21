// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggDebuffUserWidget.h"

#include "Components/ProgressBar.h"


void UYggDebuffUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UYggDebuffUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UYggDebuffUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	EndDebuff();
}

FSlateBrush MakeBrush(UTexture2D* Tex, FVector2D Size, float Brightness = 1.0f)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Tex);
	Brush.ImageSize = Size;
	Brush.TintColor = FLinearColor(Brightness, Brightness, Brightness, 1.0f);
	Brush.DrawAs = ESlateBrushDrawType::Image;
	return Brush;
}

void UYggDebuffUserWidget::InitDebuff(EStatusEffectType StatusEffectType)
{
	DebuffType = StatusEffectType;

	FVector2D Size(32.0f, 32.0f);
	SetTexture(StatusEffectType);

	FProgressBarStyle PStyle;
	PStyle.BackgroundImage = MakeBrush(Tex, Size, 0.6f);
	PStyle.FillImage = MakeBrush(Tex, Size, 1.0f);
	DebuffBar->SetWidgetStyle(PStyle);
	DebuffBar->SetPercent(1.0f);

	StartDebuff(0.0f);
}

void UYggDebuffUserWidget::StartDebuff(float Duration)
{
	DebufflTime = Duration;
	RemainingTime = Duration;

	if (DebuffBar)
	{
		DebuffBar->SetPercent(1.0f);
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UYggDebuffUserWidget::UpdateDebuffBar, 0.05f, true);
}

void UYggDebuffUserWidget::UpdateDebuffBar()
{
	RemainingTime -= 0.05f;

	if (RemainingTime <= 0.0f)
	{
		EndDebuff();
		return;
	}

	float Progress = RemainingTime / DebufflTime;
	if (DebuffBar)
	{
		DebuffBar->SetPercent(Progress);
	}
}

void UYggDebuffUserWidget::EndDebuff()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	RemoveFromParent();
}

UTexture2D* UYggDebuffUserWidget::SetTexture(EStatusEffectType StatusEffectType)
{
	switch (StatusEffectType)
	{
	case EStatusEffectType::Poison:
		return Tex = PosionTexture;
		break;
	case EStatusEffectType::Burn:
		return Tex = BurnTexture;
		break;
	case EStatusEffectType::Slow:
		return Tex = SlowTexture;
		break;
	case EStatusEffectType::Stunned:
		return Tex = StunnedTexture;
		break;
	default:
		return Tex = nullptr;
		break;
	}
}

