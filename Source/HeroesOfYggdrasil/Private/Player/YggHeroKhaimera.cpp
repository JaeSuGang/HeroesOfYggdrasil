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



#include "Component/SceneComponent/YggAttackCapsuleComponent.h"
#include "Component/SceneComponent/YggParticleSystemComponent.h"


AYggHeroKhaimera::AYggHeroKhaimera()
{
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("LeftAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh(), TEXT("weapon_l"));
		AttackCapsuleComponentMap.Add(TEXT("LeftAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("RightAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh(), TEXT("weapon_r"));
		AttackCapsuleComponentMap.Add(TEXT("RightAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillQAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponentMap.Add(TEXT("SkillQAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillEAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponentMap.Add(TEXT("SkillEAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillRAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponentMap.Add(TEXT("SkillRAttack"), AttackCapsuleComponent);
	}
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
	if (HeroAttributeComponent)
	{
		HeroAttributeComponent->ServerSetBaseData_Implementation(TEXT("Khaimera"));

	}
	
	if (HasAuthority())
	{
		UpdateStatus();
	}
}

void AYggHeroKhaimera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
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
	HeroAnimInstance->PlayMontage(MontageName);
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
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
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
	HeroAnimInstance->PlayMontage(MontageName);
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
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
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
	HeroAnimInstance->PlayMontage(MontageName);
}


void AYggHeroKhaimera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


