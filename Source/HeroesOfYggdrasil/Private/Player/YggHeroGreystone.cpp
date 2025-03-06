// Coded By AssortRock Unreal Engine Class Project

#include "Player/YggHeroGreystone.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Attribute/HeroAttributeComponent.h"

AYggHeroGreystone::AYggHeroGreystone()
{
}

AYggHeroGreystone::~AYggHeroGreystone()
{
}

void AYggHeroGreystone::BeginPlay()
{
	Super::BeginPlay();

	CurAttackIndex = 0;
	MaxAttackIndex = 4;
}

void AYggHeroGreystone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYggHeroGreystone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
			EnhancedInput->BindAction(*ActionMap.Find(FName("Move")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Move);
		}
		if (ActionMap.Find(FName("Look")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Look")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Look);
		}
		if (ActionMap.Find(FName("Jump")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Jump")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Jump);
		}
		if (ActionMap.Find(FName("Attack")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Attack);
		}
		if (ActionMap.Find(FName("SkillQ")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillQ")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::SkillQ);
		}
		if (ActionMap.Find(FName("SkillE")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillE")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::SkillE);
		}
		if (ActionMap.Find(FName("SkillR")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillR")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::SkillR);
		}
		if (ActionMap.Find(FName("ToggleAimMode")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("ToggleAimMode")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::ToggleAimMode);
		}
	}
}

void AYggHeroGreystone::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void AYggHeroGreystone::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
}

void AYggHeroGreystone::Jump(const FInputActionValue& Value)
{
}

void AYggHeroGreystone::Attack(const FInputActionValue& Value)
{
	Super::Attack(Value);

	/*if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}*/

	if (HasAuthority())
	{
		// HeroAttributeComponent->RemoveTag(TEXT("Character.State.Moveable"));
		// HeroAttributeComponent->RemoveTag(TEXT("Character.State.Attackable"));
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

void AYggHeroGreystone::ServerAttack_Implementation()
{
	Attack(FInputActionValue());
}

void AYggHeroGreystone::MulticastAttack_Implementation(int ServerAttackIndex)
{
	CurAttackIndex = ServerAttackIndex;
	
	FName MontageName = *FString::Printf(TEXT("Attack%d"), CurAttackIndex);
	
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.Buff.FastAttackSpeed")))
	{
		MontageName = *FString::Printf(TEXT("FAttack%d"), CurAttackIndex);
	}
	
	 PlayMontage(MontageName);
}

void AYggHeroGreystone::SkillQ(const FInputActionValue& Value)
{
	Super::SkillQ(Value);

	/*if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}*/
	if (HasAuthority())
	{
		//HeroAttributeComponent->RemoveTag(TEXT("Character.State.Attackable"));
		//HeroAttributeComponent->RemoveTag(TEXT("Character.State.Moveable"));
		MulticastSkillQ();
	}
	else
	{
		ServerSkillQ();
	}
}

void AYggHeroGreystone::ServerSkillQ_Implementation()
{
	SkillQ(FInputActionValue());
}

void AYggHeroGreystone::MulticastSkillQ_Implementation()
{
	FName MontageName = TEXT("SkillQ");
	PlayMontage(MontageName);
}

void AYggHeroGreystone::SkillE(const FInputActionValue& Value)
{
	Super::SkillE(Value);

	/*if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}*/
	if (HasAuthority())
	{
		//HeroAttributeComponent->RemoveTag(TEXT("Character.State.Moveable"));
		//HeroAttributeComponent->RemoveTag(TEXT("Character.State.Attackable"));
		MulticastSkillE();
	}
	else
	{
		ServerSkillE();
	}
}

void AYggHeroGreystone::ServerSkillE_Implementation()
{
	SkillE(FInputActionValue());
}

void AYggHeroGreystone::MulticastSkillE_Implementation()
{
	// FName MontageName = TEXT("SkillE");
	// PlayMontage(MontageName);
}

void AYggHeroGreystone::SkillR(const FInputActionValue& Value)
{
	Super::SkillR(Value);

	/*if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}*/
	if (HasAuthority())
	{
		//HeroAttributeComponent->RemoveTag(TEXT("Character.State.Moveable"));
		//HeroAttributeComponent->RemoveTag(TEXT("Character.State.Attackable"));
		MulticastSkillR();
	}
	else
	{
		ServerSkillR();
	}
}
void AYggHeroGreystone::ServerSkillR_Implementation()
{
	SkillR(FInputActionValue());
}

void AYggHeroGreystone::MulticastSkillR_Implementation()
{
	FName MontageName = TEXT("SkillR");
	PlayMontage(MontageName);
}