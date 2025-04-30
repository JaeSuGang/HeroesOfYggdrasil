// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggDefeatedUserWidget.h"
#include "MainGame/EnemyManager.h"

#include "StageSystem/StageSystem.h"
#include "StageSystem/Stages/BattleStage.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/YggHero.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

void UYggDefeatedUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UYggDefeatedUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Init();
	PlayAnimation(FirstAnim);
	ExitGameButton->OnClicked.AddDynamic(this, &UYggDefeatedUserWidget::OnClickSound);
}

void UYggDefeatedUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UYggDefeatedUserWidget::Init()
{
	if (UStageSystem* StageSystem = UStageSystem::Get(GetWorld()))
	{
		{
			int32 Time = StageSystem->ElapsedTimeFromStart;

			FString String = FString::Printf(TEXT("%d : %d"), Time / 60, Time % 60);

			PlayTime->SetText(FText::FromString(String));
			PlayTime->SetVisibility(ESlateVisibility::Hidden);
		}

		{
			CurWave->SetText(FText::AsNumber(StageSystem->CurrentRound));
			CurWave->SetVisibility(ESlateVisibility::Hidden);
		}

		{
			UBattleStage* BattleStage = StageSystem->GetBattleStage();

			float Percent = static_cast<float>(StageSystem->CurrentRound) / BattleStage->WaveTableAsArray.Num();

			FString String = FString::Printf(TEXT("%1.f%%"), Percent * 100);

			WaveProgress->SetText(FText::FromString(String));
			WaveProgress->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (AEnemyManager* EnemyManager = AEnemyManager::Get(GetWorld()))
	{
		MDeathCount->SetText(FText::AsNumber(EnemyManager->DeadEnemyCount));
		MDeathCount->SetVisibility(ESlateVisibility::Hidden);
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (AYggHero* Hero = PC->GetPawn<AYggHero>())
	{
		PDeathCount->SetText(FText::AsNumber(Hero->GetDeathCount()));
		PDeathCount->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UYggDefeatedUserWidget::OnClickSound()
{
	if (ClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound);
	}
}