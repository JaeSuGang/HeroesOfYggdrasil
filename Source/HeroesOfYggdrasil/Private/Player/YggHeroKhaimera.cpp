// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroKhaimera.h"

#include "Engine/LocalPlayer.h"

// Input
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "InputActionValue.h"



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
			UE_LOG(LogTemp, Warning, TEXT("MoveAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("Look")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Look")), ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Look);
			UE_LOG(LogTemp, Warning, TEXT("LookAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("Jump")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Jump")), ETriggerEvent::Triggered, this, &AYggHeroKhaimera::Jump);
			UE_LOG(LogTemp, Warning, TEXT("JumpAction Bind Succesed"));
		}

		if (ActionMap.Find(FName("Attack")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Started, this, &AYggHeroKhaimera::Attack);
			UE_LOG(LogTemp, Warning, TEXT("AttackAction Bind Succesed"));
		}
	}
}

void AYggHeroKhaimera::Attack(const FInputActionValue& _Value)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (MontageMap.Find(FName("Attack")) && AnimInstance)
	{
		if (CurCombo == MaxCombo) 
		{
			CurCombo = 0;
		}	
		switch (CurCombo)
		{
		case 0:
			FirstAttack(AnimInstance);
			break;
		case 1:
			SecondAttack(AnimInstance);
			break;
		case 2:
			LastAttack(AnimInstance);
			break;
		default:
			break;
		}
		CurCombo++;
	}
}

void AYggHeroKhaimera::FirstAttack(UAnimInstance* AnimInstance)
{
	AnimInstance->Montage_Play(*MontageMap.Find(FName("Attack")));
	GEngine->AddOnScreenDebugMessage(-1,1.0f,FColor::Blue, FString::Printf(TEXT("%d"),CurCombo));
}

void AYggHeroKhaimera::SecondAttack(UAnimInstance* AnimInstance)
{
	FName SectionName = *FString::Printf(TEXT("Attack%d"), CurCombo);
	AnimInstance->Montage_JumpToSection(SectionName,*MontageMap.Find(FName("Attack")));
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("%d"), CurCombo));
}

void AYggHeroKhaimera::LastAttack(UAnimInstance* AnimInstance)
{
	FName SectionName = *FString::Printf(TEXT("Attack%d"), CurCombo);
	AnimInstance->Montage_JumpToSection(SectionName, *MontageMap.Find(FName("Attack")));
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("%d"), CurCombo));
}
