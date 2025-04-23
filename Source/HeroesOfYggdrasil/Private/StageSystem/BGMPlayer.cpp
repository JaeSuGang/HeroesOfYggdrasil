// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/BGMPlayer.h"

#include "Components/AudioComponent.h"

#include "StageSystem/StageSystem.h"
#include "StageSystem/StageBase.h"
#include "StageSystem/Stages/ReinforceStage.h"

ABGMPlayer::ABGMPlayer()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bIsUISound = true;
	AudioComponent->bAutoActivate = false;
}

void ABGMPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayBGM(0);

	UStageSystem* US = UStageSystem::Get(GetWorld());
	US->OnStageStartedDelegate.AddDynamic(this, &ABGMPlayer::OnStartStage);
	US->OnVictory.AddDynamic(this, &ABGMPlayer::OnGameVictory);
	US->OnDefeated.AddDynamic(this, &ABGMPlayer::OnGameDefeated);
}

void ABGMPlayer::PlayBGM(int SoundIndex)
{
	USoundWave* SelectedSound = BackgroundMusics[SoundIndex];

	SelectedSound->bLooping = true;
	AudioComponent->SetSound(SelectedSound);
	AudioComponent->Play();
}

void ABGMPlayer::OnStartStage(UStageBase* NewStage)
{
	if (UReinforceStage* NewReinforceStage = Cast<UReinforceStage>(NewStage))
	{
		if (NewStage->StageSystem->CurrentRound == 1)
			PlayBGM(1);

		else if (NewStage->StageSystem->CurrentRound == 4)
			PlayBGM(2);

		else if (NewStage->StageSystem->CurrentRound == 7)
			PlayBGM(3);

		else if (NewStage->StageSystem->CurrentRound == 10)
			PlayBGM(4);
	}
}

void ABGMPlayer::OnGameVictory(FOnVictoryParams OnVictoryParams)
{
	PlayBGM(5);
}

void ABGMPlayer::OnGameDefeated(FOnDefeatedParams OnDefeatedParams)
{
	PlayBGM(6);
}

