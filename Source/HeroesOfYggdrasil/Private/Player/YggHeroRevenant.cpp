// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroRevenant.h"


// Input
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"

// Movement
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/YggHeroAnimInstance.h"

// Tag
#include "Attribute/HeroAttributeComponent.h"

// Network
#include "Net/UnrealNetwork.h"

#include "Global/YggProjectileActor.h"
#include "MainGame/UI/MainGameHUD.h"

AYggHeroRevenant::AYggHeroRevenant()
{

}

void AYggHeroRevenant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
		
	}
}



void AYggHeroRevenant::BeginPlay()
{
	Super::BeginPlay();

}

void AYggHeroRevenant::Attack(const FInputActionValue& Value)
{
	Super::Attack(Value);
}
