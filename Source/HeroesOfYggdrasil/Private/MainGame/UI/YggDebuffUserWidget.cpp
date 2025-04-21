// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggDebuffUserWidget.h"

#include "Components/ProgressBar.h"

#include "Player/YggHero.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Global/YggTickActor.h"

void UYggDebuffUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UYggDebuffUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AYggHero* Hero = PC->GetPawn<AYggHero>();

	TArray<AActor*> AttachedActors;
	Hero->GetAttachedActors(AttachedActors);

	for (AActor* Actor : AttachedActors)
	{
		if (AYggTickActor* TickActor = Cast<AYggTickActor>(Actor))
		{
			if (DebuffType == TickActor->TickEffectType)
			{
				DebuffTime = TickActor->StatusTickTime;
			}
		}
	}
}

void UYggDebuffUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	EndDebuff();
}

void UYggDebuffUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AYggHero* Hero = PC->GetPawn<AYggHero>();

	TArray<AActor*> AttachedActors;
	Hero->GetAttachedActors(AttachedActors);

	for (AActor* Actor : AttachedActors)
	{
		if (AYggTickActor* TickActor = Cast<AYggTickActor>(Actor))
		{
			if (DebuffType == TickActor->TickEffectType)
			{
				UpdateDebuffBar(TickActor->StatusTickTime);
			}
		}
	}
}

FSlateBrush UYggDebuffUserWidget::MakeTexBrush(UTexture2D* Tex, FVector2D Size, float Brightness)
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
	PStyle.BackgroundImage = MakeTexBrush(Texture, Size, 0.6f);
	PStyle.FillImage = MakeTexBrush(Texture, Size, 1.0f);
	DebuffBar->SetWidgetStyle(PStyle);
	DebuffBar->SetPercent(1.0f);

	//StartDebuff();
}

void UYggDebuffUserWidget::StartDebuff()
{
	RemainingTime = DebuffTime;

	if (DebuffBar)
	{
		DebuffBar->SetPercent(1.0f);
	}

	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UYggDebuffUserWidget::UpdateDebuffBar, 0.05f, true);
}

void UYggDebuffUserWidget::UpdateDebuffBar(float Duration)
{
	RemainingTime = Duration;

	if (RemainingTime <= 0.1f)
	{
		EndDebuff();
		return;
	}

	float Progress = RemainingTime / DebuffTime;
	if (DebuffBar)
	{
		DebuffBar->SetPercent(Progress);
	}
}

void UYggDebuffUserWidget::EndDebuff()
{
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	RemoveFromParent();
}

UTexture2D* UYggDebuffUserWidget::SetTexture(EStatusEffectType StatusEffectType)
{
	switch (StatusEffectType)
	{
	case EStatusEffectType::Poison:
		return Texture = PosionTexture;
	case EStatusEffectType::Burn:
		return Texture = BurnTexture;
	case EStatusEffectType::Slow:
		return Texture = SlowTexture;
	case EStatusEffectType::Stunned:
		return Texture = StunnedTexture;
	default:
		return Texture = nullptr;
	}
}

