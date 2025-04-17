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
		if (ActionMap.Contains(FName("Attack")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Triggered, this, &AYggHeroRevenant::Attack);
		}
		if (ActionMap.Contains(FName("SkillE")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillE")], ETriggerEvent::Triggered, this, &AYggHeroRevenant::SkillE);
		}
	}
}



void AYggHeroRevenant::BeginPlay()
{
	Super::BeginPlay();
	if (HeroAttributeComponent)
	{
		HeroAttributeComponent->ServerSetBaseData_Implementation(TEXT("Revenant"));
	}

}

void AYggHeroRevenant::Attack(const FInputActionValue& Value)
{
	if (bAimMode == false) 
	{
		SetAimMode(true);
	}
	Super::Attack(Value);
}

void AYggHeroRevenant::SkillE(const FInputActionValue& Value)
{
	if (bAimMode == false)
	{
		SetAimMode(true);
	}
	Super::SkillE(Value);
}
