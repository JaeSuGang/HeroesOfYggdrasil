// Coded By AssortRock Unreal Engine Class Project


#include "Core/YggPlayerState.h"

void AYggPlayerState::ServerSetPlayerName_Implementation(const FString& name)
{
	APlayerState::SetPlayerName(name);
}