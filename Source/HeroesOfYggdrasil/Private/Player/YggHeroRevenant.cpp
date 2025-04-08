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
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Completed, this, &AYggHeroRevenant::EndAttack);
		}

		if (ActionMap.Contains(FName("SkillQ")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillQ")], ETriggerEvent::Started, this, &AYggHeroRevenant::SkillQ);
		}

		if (ActionMap.Contains(FName("SkillE")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillE")], ETriggerEvent::Started, this, &AYggHeroRevenant::SkillE);
		}

		if (ActionMap.Contains(FName("SkillR")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillR")], ETriggerEvent::Started, this, &AYggHeroRevenant::SkillR);
		}
	}
}
void AYggHeroRevenant::SkillQ(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		MulticastSkillQ(Value);
	}
	else
	{
		ServerSkillQ(Value);
	}
}

void AYggHeroRevenant::ServerSkillQ_Implementation(const FInputActionValue& Value)
{
	SkillQ(Value);
}

void AYggHeroRevenant::MulticastSkillQ_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillQ");
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHeroRevenant::SkillE(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		MulticastSkillE(Value);
	}
	else
	{
		ServerSkillE(Value);
	}
}

void AYggHeroRevenant::ServerSkillE_Implementation(const FInputActionValue& Value)
{
	SkillE(Value);
}



void AYggHeroRevenant::MulticastSkillE_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillE");
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHeroRevenant::SkillR(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		MulticastSkillR(Value);
	}
	else
	{
		ServerSkillR(Value);
	}
}

void AYggHeroRevenant::ServerSkillR_Implementation(const FInputActionValue& Value)
{
	SkillR(Value);
}

void AYggHeroRevenant::MulticastSkillR_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillR");
	HeroAnimInstance->PlayMontage(MontageName);
}
