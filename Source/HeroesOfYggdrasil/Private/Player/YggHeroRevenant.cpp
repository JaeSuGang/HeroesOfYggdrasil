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
#include "Global/YggBombActor.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Kismet/GameplayStatics.h"

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
		if (ActionMap.Contains(FName("SkillQ")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillQ")], ETriggerEvent::Triggered, this, &AYggHeroRevenant::SkillQ);
		}
		if (ActionMap.Contains(FName("SkillR")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillR")], ETriggerEvent::Triggered, this, &AYggHeroRevenant::SkillR);
		}
	}
}

void AYggHeroRevenant::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AYggHeroRevenant, AimDirection);
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
	FVector NewAimDir = Local_GetAimDirection(LeftSocketName);
	Server_SetAimDirection(NewAimDir);
	Super::Attack(Value);
}




void AYggHeroRevenant::SkillQ(const FInputActionValue& Value)
{
	if (bAimMode == false)
	{
		SetAimMode(true);
	}
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	FVector NewAimDir = Local_GetAimDirection(LeftSocketName);
	Server_SetAimDirection(NewAimDir);
	HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
	if (HasAuthority())
	{
		MulticastHeroSkillQ(Value);
	}
	else
	{
		ServerHeroSkillQ(Value);
	}

	float CoolTime = HeroAttributeComponent->SkillQMaxCoolTime;
	OnSkillQ.Broadcast(FName("SkillQ"), CoolTime);
}

void AYggHeroRevenant::SkillE(const FInputActionValue& Value)
{
	if (bAimMode == false)
	{
		SetAimMode(true);
	}
	FVector NewAimDir = Local_GetAimDirection(RightSocketName);
	Server_SetAimDirection(NewAimDir);
	Super::SkillE(Value);
}

void AYggHeroRevenant::SkillR(const FInputActionValue& Value)
{
	if (bAimMode == false)
	{
		SetAimMode(true);
	}
	FVector NewAimDir = Local_GetAimDirection(TEXT("None"));
	Server_SetAimDirection(NewAimDir);
	bIsUsingSkillR = true;
	Super::SkillR(Value);
}

void AYggHeroRevenant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bAimMode)
	{
		FVector NewAimDir = Local_GetAimDirection(LeftSocketName);
		Server_SetAimDirection(NewAimDir);
	}
}



