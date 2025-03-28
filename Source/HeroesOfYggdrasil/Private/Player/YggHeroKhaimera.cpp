// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroKhaimera.h"

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

#include "Attribute/KhaimeraAttributeComponent.h"

// collison
#include "Components/BoxComponent.h"

#include "Data/YggStructData.h"

#include "Component/CaptureComponent.h"






AYggHeroKhaimera::AYggHeroKhaimera()
{
	KhaimeraAttributeComponent = Cast<UKhaimeraAttributeComponent>(HeroAttributeComponent);
	/*AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCapsule"));
	AttackBox->SetupAttachment(RootComponent);*/

	
}

void AYggHeroKhaimera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
		if (ActionMap.Contains(FName("Attack")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Attack);
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Completed, this, &AYggHeroKhaimera::EndAttack);
		}

		if (ActionMap.Contains(FName("SkillQ")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillQ")], ETriggerEvent::Started, this, &AYggHeroKhaimera::SkillQ);
		}

		if (ActionMap.Contains(FName("SkillE")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillE")], ETriggerEvent::Started, this, &AYggHeroKhaimera::SkillE);
		}

		if (ActionMap.Contains(FName("SkillR")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillR")], ETriggerEvent::Started, this, &AYggHeroKhaimera::SkillR);
		}
	}
}

void AYggHeroKhaimera::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed *= HeroAttributeComponent->SpeedRate;
	GetCharacterMovement()->JumpZVelocity *= HeroAttributeComponent->JumpRate;
}

void AYggHeroKhaimera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYggHeroKhaimera::Attack(const FInputActionValue& Value)
{
	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.PressedAttack")))
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.PressedAttack"));
	}
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastAttack(Value);
	}
	else
	{
		ServerAttack(Value);
		return;
	}
}

void AYggHeroKhaimera::ServerAttack_Implementation(const FInputActionValue& Value)
{
	Attack(Value);
}

void AYggHeroKhaimera::MulticastAttack_Implementation(const FInputActionValue& Value)
{

	FName MontageName = *FString::Printf(TEXT("Attack"));
	HeroAnimInstance->PlayMontage(MontageName, HeroAttributeComponent->SpeedRate);
}




void AYggHeroKhaimera::EndAttack(const FInputActionValue& Value)
{
	HeroAttributeComponent->RemoveTag(TEXT("Character.State.PressedAttack"));
}

void AYggHeroKhaimera::SkillQ(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastSkillQ(Value);
	}
	else
	{
		ServerSkillQ(Value);
	}
}

void AYggHeroKhaimera::ServerSkillQ_Implementation(const FInputActionValue& Value)
{
	SkillQ(Value);
}

void AYggHeroKhaimera::MulticastSkillQ_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillQ");
	HeroAnimInstance->PlayMontage(MontageName, HeroAttributeComponent->SpeedRate);
}

void AYggHeroKhaimera::SkillE(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastSkillE(Value);
	}
	else
	{
		ServerSkillE(Value);
	}
}

void AYggHeroKhaimera::ServerSkillE_Implementation(const FInputActionValue& Value)
{
	SkillE(Value);
}



void AYggHeroKhaimera::MulticastSkillE_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillE");
	HeroAnimInstance->PlayMontage(MontageName, HeroAttributeComponent->SpeedRate);
}

void AYggHeroKhaimera::SkillR(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastSkillR(Value);
	}
	else
	{
		ServerSkillR(Value);
	}
}
void AYggHeroKhaimera::ServerSkillR_Implementation(const FInputActionValue& Value)
{
	SkillR(Value);
}

void AYggHeroKhaimera::MulticastSkillR_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillR");
	HeroAnimInstance->PlayMontage(MontageName, HeroAttributeComponent->SpeedRate);
}


void AYggHeroKhaimera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AYggHeroKhaimera, KhaimeraAttributeComponent);
}








