// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroKhaimera.h"

#include "Engine/LocalPlayer.h"

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



AYggHeroKhaimera::AYggHeroKhaimera()
{
	KhaimeraAttributeComponent = Cast<UKhaimeraAttributeComponent>(HeroAttributeComponent);
}


void AYggHeroKhaimera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
		if (ActionMap.Find(FName("Move")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Move")), ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Move);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera MoveAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("Look")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Look")), ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Look);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera LookAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("Jump")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Jump")), ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Jump);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera JumpAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("Attack")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Attack);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera AttackAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("SkillQ")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillQ")), ETriggerEvent::Started, this, &AYggHeroKhaimera::SkillQ);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera AttackAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("SkillE")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillE")), ETriggerEvent::Started, this, &AYggHeroKhaimera::SkillE);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera AttackAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("SkillR")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillR")), ETriggerEvent::Started, this, &AYggHeroKhaimera::SkillR);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera AttackAction Bind Succesed"));
		}
	}
}

void AYggHeroKhaimera::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed *= HeroAttributeComponent->SpeedRate;
	GetCharacterMovement()->JumpZVelocity *= HeroAttributeComponent->JumpRate;

	CurAttackIndex = 0;
	MaxAttackIndex = 3;

}

void AYggHeroKhaimera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYggHeroKhaimera::Move(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotMoveable")))
	{
		return;
	}
	Super::Move(Value);
}

void AYggHeroKhaimera::Jump()
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotMoveable")))
	{
		return;
	}
	Super::Jump();
}

#pragma region Attack
void AYggHeroKhaimera::Attack(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}

	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastAttack(CurAttackIndex);

		CurAttackIndex++;
		if (CurAttackIndex == MaxAttackIndex)
		{
			CurAttackIndex = 0;
		}
	}
	else
	{
		ServerAttack();
		return;
	}
}

void AYggHeroKhaimera::ServerAttack_Implementation()
{
	Attack(FInputActionValue());
}

void AYggHeroKhaimera::MulticastAttack_Implementation(int ServerAttackIndex)
{
	CurAttackIndex = ServerAttackIndex; // 서버에서 동기화된 값을 클라이언트가 받음
	FName MontageName = *FString::Printf(TEXT("Attack%d"), CurAttackIndex);
	HeroAnimInstance->PlayMontage(MontageName, HeroAttributeComponent->SpeedRate);
}
#pragma endregion

#pragma region SkillQ
void AYggHeroKhaimera::SkillQ(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastSkillQ();
	}
	else
	{
		ServerSkillQ();
	}
}

void AYggHeroKhaimera::ServerSkillQ_Implementation()
{
	SkillQ(FInputActionValue());
}

void AYggHeroKhaimera::MulticastSkillQ_Implementation()
{
	FName MontageName = TEXT("SkillQ");
	HeroAnimInstance->PlayMontage(MontageName, HeroAttributeComponent->SpeedRate);
}

#pragma endregion

#pragma region SkillE
void AYggHeroKhaimera::SkillE(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastSkillE();
	}
	else
	{
		ServerSkillE();
	}
}

void AYggHeroKhaimera::ServerSkillE_Implementation()
{
	SkillE(FInputActionValue());
}



void AYggHeroKhaimera::MulticastSkillE_Implementation()
{
	FName MontageName = TEXT("SkillE");
	HeroAnimInstance->PlayMontage(MontageName, HeroAttributeComponent->SpeedRate);
}
#pragma endregion

#pragma region SkillR
void AYggHeroKhaimera::SkillR(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastSkillR();
	}
	else
	{
		ServerSkillR();
	}
}
void AYggHeroKhaimera::ServerSkillR_Implementation()
{
	SkillR(FInputActionValue());
}



void AYggHeroKhaimera::MulticastSkillR_Implementation()
{
	FName MontageName = TEXT("SkillR");
	HeroAnimInstance->PlayMontage(MontageName, HeroAttributeComponent->SpeedRate);
}
#pragma endregion


void AYggHeroKhaimera::StartSkillR()
{
	HeroAttributeComponent->AddTag(TEXT("Character.Buff.FastAttackSpeed"));
}

void AYggHeroKhaimera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AYggHeroKhaimera::SaveAttack()
{
	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotAttackable"));
}

void AYggHeroKhaimera::ResetCombo()
{
	CurAttackIndex = 0;
	HeroAttributeComponent->RemoveTags({ TEXT("Character.State.NotAttackable"),TEXT("Character.State.NotMoveable") });
}






