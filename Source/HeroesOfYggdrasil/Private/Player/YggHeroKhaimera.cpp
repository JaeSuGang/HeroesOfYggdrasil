// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroKhaimera.h"

#include "Engine/LocalPlayer.h"

// Input
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "InputActionValue.h"



AYggHeroKhaimera::AYggHeroKhaimera()
{

}

void AYggHeroKhaimera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}



	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
		
		/*if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Move);
		}
		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Look);
		}
		if (JumpAction)
		{
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Jump);
		}
		if (AttackAction)
		{
			EnhancedInput->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Attack);
		}*/
	}
}

void AYggHeroKhaimera::Attack(const FInputActionValue& _Value)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (TestAttack && AnimInstance)
	{
		AnimInstance->Montage_Play(TestAttack);
	}
}
