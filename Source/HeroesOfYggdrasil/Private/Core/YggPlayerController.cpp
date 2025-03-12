// Coded By AssortRock Unreal Engine Class Project


#include "Core/YggPlayerController.h"

#include "Net/UnrealNetwork.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "MainGame/PlayerSelectZone.h"

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
		EnhancedInputComponent->BindAction(InputModeAction, ETriggerEvent::Started, this, &AYggPlayerController::SetMouseMode);
		EnhancedInputComponent->BindAction(InputModeAction, ETriggerEvent::Completed, this, &AYggPlayerController::SetMouseMode);
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

void AYggPlayerController::SetMouseMode(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();

	if (bPressed)
	{
		int nX;
		int nY;
		GetViewportSize(nX, nY);
		SetMouseLocation(nX / 2, nY / 2);
		bShowMouseCursor = true;

		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("Pressed"));
	}
	else
	{
		
		bShowMouseCursor = false;
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
