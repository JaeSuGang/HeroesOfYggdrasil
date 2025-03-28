// Coded By AssortRock Unreal Engine Class Project


#include "Core/YggPlayerController.h"

#include "Net/UnrealNetwork.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "MainGame/PlayerSelectZone.h"
#include "Player/YggHero.h"
#include "Attribute/CharacterAttributeComponent.h"

AYggPlayerController::AYggPlayerController(const FObjectInitializer& ObjectInitializer)
    :
    Super(ObjectInitializer)
{
	TeamID = FGenericTeamId{ 0 };
}

void AYggPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputModeAction, ETriggerEvent::Started, this, &AYggPlayerController::ToggleMouseMode);
	}


}

void AYggPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void AYggPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYggPlayerController, TeamID);
}

void AYggPlayerController::TestTakeDamage(float fDamage)
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, FString::Printf(TEXT("Damage Taken : %f"), fDamage));
	if (UCharacterAttributeComponent* Attribute = GetPawn()->GetComponentByClass<UCharacterAttributeComponent>())
	{
		Attribute->Server_TakeDamage(fDamage);
	}
}

void AYggPlayerController::SetGenericTeamId_Implementation(const FGenericTeamId& _TeamID)
{
	TeamID = _TeamID;
}

void AYggPlayerController::ToggleMouseMode()
{
	bMouseMode = !bMouseMode;

	if (bMouseMode)
	{
		int nX, nY;
		GetViewportSize(nX, nY);
		SetMouseLocation(nX / 2, nY / 2);
		bShowMouseCursor = true;

		SetInputMode(FInputModeGameAndUI{});
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			EnhancedInputSubsystem->AddMappingContext(UIModeMappingContext, (int)(EInputMappingContextPriority::UIMode));
			if (AYggHero* Hero = Cast<AYggHero>(GetPawn()))
			{
				if (UInputMappingContext* IMC = Hero->GetInputMappingContext())
				{
					CharacterMappingContextToRestore = IMC;
					EnhancedInputSubsystem->RemoveMappingContext(IMC);
				}
			}
		}

		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("Pressed"));
	}
	else
	{
		bShowMouseCursor = false;

		SetInputMode(FInputModeGameOnly{});
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			EnhancedInputSubsystem->RemoveMappingContext(UIModeMappingContext);
			if (CharacterMappingContextToRestore)
			{
				EnhancedInputSubsystem->AddMappingContext(CharacterMappingContextToRestore, (int)EInputMappingContextPriority::Character);

			}
		}

		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, TEXT("Released"));
	}
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
