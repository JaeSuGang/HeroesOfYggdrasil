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


// Tag
#include "Attribute/HeroAttributeComponent.h"

// Network
#include "Net/UnrealNetwork.h"



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
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Started, this, &AYggHeroKhaimera::Attack);
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
	CurCombo = 0;
	MaxCombo = 3;
	
}

void AYggHeroKhaimera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Attack
void AYggHeroKhaimera::Attack(const FInputActionValue& Value)
{
	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}

	if (HasAuthority())
	{
		if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.MoveAttackable")))
		{
			HeroAttributeComponent->RemoveTag(TEXT("Character.State.Moveable"));
		}
		HeroAttributeComponent->RemoveTag(TEXT("Character.State.Attackable"));
		MulticastAttack(CurCombo);

		CurCombo++;
		if (CurCombo == MaxCombo)
		{
			CurCombo = 0;
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

void AYggHeroKhaimera::MulticastAttack_Implementation(int NewCurCombo)
{
	CurCombo = NewCurCombo; // 서버에서 동기화된 값을 클라이언트가 받음
	FName MontageName = *FString::Printf(TEXT("Attack%d"), CurCombo);

	PlayMontage(MontageName);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("%d"), CurCombo));
}
#pragma endregion

#pragma region SkillQ
void AYggHeroKhaimera::SkillQ(const FInputActionValue& Value)
{
	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.MoveAttackable")))
		{
			HeroAttributeComponent->RemoveTag(TEXT("Character.State.Moveable"));
		}
		HeroAttributeComponent->RemoveTag(TEXT("Character.State.Attackable"));
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
	PlayMontage(MontageName);
}

#pragma endregion

#pragma region SkillE
void AYggHeroKhaimera::SkillE(const FInputActionValue& Value)
{
	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.MoveAttackable")))
		{
			HeroAttributeComponent->RemoveTag(TEXT("Character.State.Moveable"));
		}
		HeroAttributeComponent->RemoveTag(TEXT("Character.State.Attackable"));
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
	PlayMontage(MontageName);
}
#pragma endregion

#pragma region SkillR
void AYggHeroKhaimera::SkillR(const FInputActionValue& Value)
{
	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.MoveAttackable")))
		{
			HeroAttributeComponent->RemoveTag(TEXT("Character.State.Moveable"));
		}
		HeroAttributeComponent->RemoveTag(TEXT("Character.State.Attackable"));
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
	PlayMontage(MontageName);
}
#pragma endregion


void AYggHeroKhaimera::StartSkillR()
{
	HeroAttributeComponent->AddTag(TEXT("Character.State.MoveAttackable"));
	bUsingSkillR = true;
}

void AYggHeroKhaimera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AYggHeroKhaimera::SaveAttack()
{
	HeroAttributeComponent->AddTag(TEXT("Character.State.Attackable"));
}

void AYggHeroKhaimera::ResetCombo()
{
	CurCombo = 0;
	HeroAttributeComponent->AddTags({ TEXT("Character.State.Attackable"),TEXT("Character.State.Moveable") });
}






