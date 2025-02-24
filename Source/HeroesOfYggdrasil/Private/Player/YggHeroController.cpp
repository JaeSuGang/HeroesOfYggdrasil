// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Test/TestAnimInstance_kjh.h"

#include "Player/YggHero.h"

void AYggHeroController::BeginPlay()
{
    Super::BeginPlay(); 

    HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AYggHeroController::GetGenericTeamId() const
{
    return HeroTeamID;
}


void AYggHeroController::SetupInputComponent()
{
    Super::SetupInputComponent();
}


