// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroKhaimera.h"

#include "Engine/LocalPlayer.h"

// Input
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "InputActionValue.h"
#include "Attribute/AttributeComponent.h"



AYggHeroKhaimera::AYggHeroKhaimera()
{
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
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

void AYggHeroKhaimera::Attack(const FInputActionValue& Value)
{
	if (!bIsAttackable)
	{
		return;
	}
	bIsAttackable = false;
	bIsMoveable = false;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	FName MontageName = *FString::Printf(TEXT("Attack%d"), CurCombo);
	if (MontageMap.Find(MontageName) && AnimInstance)
	{
		AnimInstance->Montage_Play(*MontageMap.Find(MontageName));
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("%d"), CurCombo));
	}
}

void AYggHeroKhaimera::SkillQ(const FInputActionValue& Value)
{
	if (!bIsAttackable)
	{
		return;
	}
	bIsAttackable = false;
	bIsMoveable = false;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	FName MontageName = TEXT("SkillQ");
	if (MontageMap.Find(MontageName) && AnimInstance)
	{
		AnimInstance->Montage_Play(*MontageMap.Find(MontageName));
		
	}
}

void AYggHeroKhaimera::SkillE(const FInputActionValue& Value)
{
	if (!bIsAttackable)
	{
		return;
	}
	bIsAttackable = false;
	bIsMoveable = false;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	FName MontageName = TEXT("SkillE");
	if (MontageMap.Find(MontageName) && AnimInstance)
	{
		AnimInstance->Montage_Play(*MontageMap.Find(MontageName));
		
	}
}

void AYggHeroKhaimera::SkillR(const FInputActionValue& Value)
{
	if (!bIsAttackable)
	{
		return;
	}
	bIsAttackable = false;
	bIsMoveable = false;
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	FName MontageName = TEXT("SkillR");
	if (MontageMap.Find(MontageName) && AnimInstance)
	{
		AnimInstance->Montage_Play(*MontageMap.Find(MontageName));
		
	}
}



void AYggHeroKhaimera::Move(const FInputActionValue& Value)
{
	if (!bIsMoveable)
	{
		return;
	}
	FVector2D MovementVector = Value.Get<FVector2D>();
	FRotator ControllerRotation = GetControlRotation();

	FRotator YawRotation(0, ControllerRotation.Yaw, 0);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}




void AYggHeroKhaimera::SaveAttack()
{
	CurCombo++;
	if (CurCombo == MaxCombo) 
	{
		CurCombo = 0;
	}
	bIsAttackable = true;
}

void AYggHeroKhaimera::ResetCombo()
{
	CurCombo = 0;
	bIsAttackable = true;
	bIsMoveable = true;
}




