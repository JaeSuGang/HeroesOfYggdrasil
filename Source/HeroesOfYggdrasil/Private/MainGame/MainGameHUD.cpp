// AssortRock 


#include "MainGame/MainGameHUD.h"

void AMainGameHUD::BeginPlay()
{
	Super::BeginPlay();

	GetOwningPlayerController()->SetInputMode(FInputModeGameOnly{});
}
