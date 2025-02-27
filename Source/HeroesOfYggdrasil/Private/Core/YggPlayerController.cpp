// Coded By AssortRock Unreal Engine Class Project


#include "Core/YggPlayerController.h"

AYggPlayerController::AYggPlayerController(const FObjectInitializer& ObjectInitializer)
    :
    Super(ObjectInitializer)
{
	TeamID = FGenericTeamId{ 0 };
}

FGenericTeamId AYggPlayerController::GetGenericTeamId() const
{
    return TeamID;
}