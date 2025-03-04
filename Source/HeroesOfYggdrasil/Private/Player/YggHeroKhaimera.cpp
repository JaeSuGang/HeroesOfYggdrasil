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
	HeroAttributeComponent = CreateDefaultSubobject<UHeroAttributeComponent>(TEXT("AttributeComponent"));
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
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Completed, this, &AYggHeroKhaimera::Attack);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera AttackAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("SkillQ")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillQ")), ETriggerEvent::Completed, this, &AYggHeroKhaimera::SkillQ);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera AttackAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("SkillE")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillE")), ETriggerEvent::Completed, this, &AYggHeroKhaimera::SkillE);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera AttackAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("SkillR")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillR")), ETriggerEvent::Completed, this, &AYggHeroKhaimera::SkillR);
			UE_LOG(LogTemp, Warning, TEXT("Khaimera AttackAction Bind Succesed"));
		}
	}
}

void AYggHeroKhaimera::BeginPlay()
{
	Super::BeginPlay();
	ResetCombo();
}

#pragma region Attack
void AYggHeroKhaimera::Attack(const FInputActionValue& Value)
{
	if (!HasAuthority())
	{
		ServerAttack();
		return;
	}

	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}

	HeroAttributeComponent->RemoveTags({ TEXT("Character.State.Attackable"),TEXT("Character.State.Moveable") });
	MulticastAttack();

}
void AYggHeroKhaimera::ServerAttack_Implementation()
{
	Attack(FInputActionValue());
}

bool AYggHeroKhaimera::ServerAttack_Validate()
{
	// 여기에 태그 조건인가?
	return true;
}

void AYggHeroKhaimera::MulticastAttack_Implementation()
{
	// 몽타주 실행
	FName MontageName = *FString::Printf(TEXT("Attack%d"), CurCombo);
	if (MontageMap.Find(MontageName))
	{
		PlayAnimMontage(*MontageMap.Find(MontageName));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("%d"), CurCombo));
	}
}
#pragma endregion

#pragma region SkillQ
void AYggHeroKhaimera::SkillQ(const FInputActionValue& Value)
{

	if (!HasAuthority())
	{
		ServerSkillQ();
		return;
	}

	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}

	HeroAttributeComponent->RemoveTags({ TEXT("Character.State.Attackable"), TEXT("Character.State.Moveable") });
	MulticastSkillQ();
}

void AYggHeroKhaimera::ServerSkillQ_Implementation()
{
	SkillQ(FInputActionValue());
}

bool AYggHeroKhaimera::ServerSkillQ_Validate()
{
	return true;
}

void AYggHeroKhaimera::MulticastSkillQ_Implementation()
{
	FName MontageName = TEXT("SkillQ");
	if (MontageMap.Find(MontageName))
	{
		PlayAnimMontage(*MontageMap.Find(MontageName));
	}
}

#pragma endregion

#pragma region SkillE
void AYggHeroKhaimera::SkillE(const FInputActionValue& Value)
{
	if (!HasAuthority())
	{
		ServerSkillE();
		return;
	}

	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}

	HeroAttributeComponent->RemoveTags({ TEXT("Character.State.Attackable"), TEXT("Character.State.Moveable") });
	MulticastSkillE();
}

void AYggHeroKhaimera::ServerSkillE_Implementation()
{
	SkillE(FInputActionValue());
}

bool AYggHeroKhaimera::ServerSkillE_Validate()
{
	return true;
}

void AYggHeroKhaimera::MulticastSkillE_Implementation()
{
	FName MontageName = TEXT("SkillE");
	if (MontageMap.Find(MontageName))
	{
		PlayAnimMontage(*MontageMap.Find(MontageName));
	}
}
#pragma endregion

#pragma region SkillR
void AYggHeroKhaimera::SkillR(const FInputActionValue& Value)
{
	if (!HasAuthority())
	{
		ServerSkillR();
		return;
	}

	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Attackable")))
	{
		return;
	}

	HeroAttributeComponent->RemoveTags({ TEXT("Character.State.Attackable"), TEXT("Character.State.Moveable") });
	MulticastSkillR();
}
void AYggHeroKhaimera::ServerSkillR_Implementation()
{
	SkillR(FInputActionValue());
}

bool AYggHeroKhaimera::ServerSkillR_Validate()
{
	return true;
}

void AYggHeroKhaimera::MulticastSkillR_Implementation()
{
	FName MontageName = TEXT("SkillR");
	if (MontageMap.Find(MontageName))
	{
		PlayAnimMontage(*MontageMap.Find(MontageName));
	}
}
#pragma endregion















void AYggHeroKhaimera::Move(const FInputActionValue& Value)
{
	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.Moveable")))
	{
		return;
	}
	Super::Move(Value);
}

void AYggHeroKhaimera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AYggHeroKhaimera, CurCombo);
}

void AYggHeroKhaimera::SaveAttack()
{
	CurCombo++;
	if (CurCombo == MaxCombo)
	{
		CurCombo = 0;
	}
	HeroAttributeComponent->AddTag(TEXT("Character.State.Attackable"));
}

void AYggHeroKhaimera::ResetCombo()
{
	CurCombo = 0;
	HeroAttributeComponent->AddTags({ TEXT("Character.State.Attackable"),TEXT("Character.State.Moveable") });
}






