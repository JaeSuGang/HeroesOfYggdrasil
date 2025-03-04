// Coded By AssortRock Unreal Engine Class Project


#include "Core/YggPlayerController.h"

#include "Net/UnrealNetwork.h"

#include "MainGame/PlayerSelectZone.h"

AYggPlayerController::AYggPlayerController(const FObjectInitializer& ObjectInitializer)
    :
    Super(ObjectInitializer)
{
	TeamID = FGenericTeamId{ 0 };
}

void AYggPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYggPlayerController, TeamID);
}

void AYggPlayerController::Test()
{
	APlayerSelectZone* PSZ = Cast<APlayerSelectZone>(GetPawn());
	if (PSZ)
	{

	}
}

void AYggPlayerController::SetGenericTeamId_Implementation(const FGenericTeamId& _TeamID)
{
	TeamID = _TeamID;
}

FGenericTeamId AYggPlayerController::GetGenericTeamId() const
{
    return TeamID;
}

void AYggPlayerController::SetInputEnabled(bool Value)
{
    if (Value)
        GetPawn()->EnableInput(this);    
    else
        GetPawn()->DisableInput(this);
}
