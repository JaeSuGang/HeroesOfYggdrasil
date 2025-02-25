// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGameState.h"

#include "MainGame/MainGameHUD.h"
#include "Kismet/GameplayStatics.h"

void AMainGameState::OnEnterReadyFinishedGameState_Implementation()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (AMainGameHUD* MGH = Cast<AMainGameHUD>(PC->GetHUD()))
		{
			MGH->CloseCurentWidget();
			MGH->ShowMainGameWidget();
		}
	}


}
