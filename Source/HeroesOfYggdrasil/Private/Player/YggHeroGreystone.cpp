// Coded By AssortRock Unreal Engine Class Project

// Project Headers
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"

// Unreal Framework Core Components
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"

// Input System Modules
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Visual Components
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"

// Engine Utilities
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"

#include "Animation/HeroGreystoneAnimInstance.h"
#include "Components/CapsuleComponent.h"

#include "Engine/DataTable.h"
#include "Data/YggStructData.h"

AYggHeroGreystone::AYggHeroGreystone()
{
}

AYggHeroGreystone::~AYggHeroGreystone()
{
}

void AYggHeroGreystone::BeginPlay()
{
	Super::BeginPlay();

	HeroAttributeComponent->SetCombo(4);

	// HeroAttributeComponent->Status = *(HeroAttributeComponent->Data->FindRow<FHeroBaseStatusInfoRow>(TEXT("Greystone"), TEXT("Context")));
}

void AYggHeroGreystone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);		

	if (bIsSkillR)
	{
		MagicCircleOn();
	}
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
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Started, this, &AYggHeroGreystone::AttackPressed);
		}
		if (ActionMap.Find(FName("Attack")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Completed, this, &AYggHeroGreystone::AttackReleased);
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
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotMoveable")))
	{
		return;
	}

	Super::Move(Value);
}

void AYggHeroGreystone::Jump(const FInputActionValue& Value)
{
}

void AYggHeroGreystone::AttackPressed(const FInputActionValue& Value)
{
	bAttackButtonPressed = true;

	// 공격 중이 아닐 때만 공격 시작

	if (!(HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("NotAttackable"));
	}

	if (!bIsAttacking && !(HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack"));

		Attack(Value);
	}
}

void AYggHeroGreystone::AttackReleased(const FInputActionValue& Value)
{
	UAnimMontage* CurrentPlayingMontage = HeroAnimInstance->GetCurrentActiveMontage();

	HeroAnimInstance->Montage_SetPlayRate(CurrentPlayingMontage, 0.0f);

	StopAttack();

	if (CurrentPlayingMontage)
	{
		FString SectionName = FString::Printf(TEXT("StopAtt%d"), HeroAttributeComponent->GetCurComboAttack());
		FName CurrentSectionName(*SectionName);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, SectionName);
				
		FTimerHandle TimerHandle;
		float ElapsedTime = 0.0f;
		float MaxWaitTime = 2.0f;

		GetWorld()->GetTimerManager().SetTimer(
			AttackStopCheckHandle,
			[this, SectionName, CurrentSectionName, CurrentPlayingMontage, MaxWaitTime, ElapsedTime]() mutable
		{
			ElapsedTime += 0.01f;

			FName CurrentSection = this->HeroAnimInstance->Montage_GetCurrentSection(CurrentPlayingMontage);

			if (CurrentSection == CurrentSectionName)
			{
				this->HeroAttributeComponent->ResetComboAttack();
				this->HeroAnimInstance->Montage_SetPlayRate(CurrentPlayingMontage, 0.0f);
				this->GetWorld()->GetTimerManager().ClearTimer(AttackStopCheckHandle);

				this->bIsAttacking = false;
				this->bAttackButtonPressed = false;
				this->HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotAttackable"));
			}
			else if (ElapsedTime >= MaxWaitTime)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Timer Cleared: Section Not Found in Time"));
				this->GetWorld()->GetTimerManager().ClearTimer(AttackStopCheckHandle);

				this->bIsAttacking = false;
				this->bAttackButtonPressed = false;
				this->HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotAttackable"));
			}
		},
			0.01f, true
		);
	}
}

void AYggHeroGreystone::Attack(const FInputActionValue& Value)
{
	if (bIsSkillR && !(HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))))
	{
		RFall();
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MagicCircleOff();
	}

	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}

	bIsAttacking = true;

	Super::Attack(Value);
	
	if (HasAuthority())
	{
		MulticastAttack(HeroAttributeComponent->GetCurComboAttack());

		if (HeroAttributeComponent->GetCurComboAttack() == HeroAttributeComponent->GetMaxComboAttack())
		{
			HeroAttributeComponent->ResetComboAttack();
		}
	}
	else
	{
		ServerAttack();
		return;
	}
}

void AYggHeroGreystone::StopAttack()
{	
	if (HasAuthority())
	{
		MulticastStopAttack();
	}
	else
	{
		ServerStopAttack();
	}
}

void AYggHeroGreystone::ServerStopAttack_Implementation()
{
	StopAttack();
}

void AYggHeroGreystone::MulticastStopAttack_Implementation()
{
	UAnimMontage* CurrentPlayingMontage = HeroAnimInstance->GetCurrentActiveMontage();

	HeroAnimInstance->Montage_SetPlayRate(CurrentPlayingMontage, 0.0f);
}

void AYggHeroGreystone::ServerAttack_Implementation()
{
	Attack(FInputActionValue());
}

void AYggHeroGreystone::MulticastAttack_Implementation(int ServerAttackIndex)
{	
	FName MontageName = *FString::Printf(TEXT("Attack"));
	
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHeroGreystone::SkillQ(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))) return;

	Super::SkillQ(Value);

	if (HasAuthority())
	{
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
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHeroGreystone::SkillE(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))) return;

	Super::SkillE(Value);

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
	FName MontageName = TEXT("SkillE");
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHeroGreystone::SkillR(const FInputActionValue& Value)
{
	if (bIsSkillR) return;

	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))) return;	

	Super::SkillR(Value);

	if (HasAuthority())
	{
		// HeroAttributeComponent->Status.GroundSpeedRate = 4.0f;
		// GetCharacterMovement()->MaxWalkSpeed *= HeroAttributeComponent->Status.GroundSpeedRate;

		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastSkillR();
	}
	else
	{
		ServerSkillR();
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;

		CameraBoom->bUsePawnControlRotation = false;
		CameraBoom->TargetArmLength = 1000.0f;
		CameraBoom->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

		PlayerController->bShowMouseCursor = true;
		PlayerController->SetIgnoreLookInput(true);

		FRotator NewControlRotation = GetActorRotation();
		PlayerController->SetControlRotation(NewControlRotation);
	}

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	bIsSkillR = true;
}

void AYggHeroGreystone::ServerSkillR_Implementation()
{
	SkillR(FInputActionValue());
}

void AYggHeroGreystone::MulticastSkillR_Implementation()
{
	FName MontageName = TEXT("SkillR");
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHeroGreystone::RFall()
{
	if (HasAuthority())
	{
		MulticastRFall();
	}
	else
	{
		ServerRFall();
	}
}

void AYggHeroGreystone::ServerRFall_Implementation()
{
	RFall();
}

void AYggHeroGreystone::MulticastRFall_Implementation()
{
	HeroAnimInstance->JumpMontage(TEXT("SkillR"), TEXT("GreystoneRFall"));
}

void AYggHeroGreystone::MagicCircleOn()
{
	FVector WorldLocation, WorldDirection;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController && PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 5000.0f);

		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
		{
			FVector OutHitLocation = HitResult.ImpactPoint;

			if (!IsValid(SkillRDecal))
			{
				SkillRDecal = UGameplayStatics::SpawnDecalAtLocation(
					GetWorld(),
					SkillRDecalMaterial,
					FVector(1024.0f, 1024.0f, 1024.0f),
					OutHitLocation,
					FRotator(-90.0f, 0.0f, 0.0f),
					0.0f
				);
			}
			else
			{
				SkillRDecal->SetWorldLocation(OutHitLocation);
			}
		}
	}
}

void AYggHeroGreystone::MagicCircleOff()
{
	bIsSkillR = false;

	if (IsValid(SkillRDecal))
	{
		SetActorLocation(SkillRDecal->GetComponentLocation());

		SkillRDecal->DestroyComponent();
		SkillRDecal = nullptr;

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			GetCharacterMovement()->bOrientRotationToMovement = true;

			CameraBoom->bUsePawnControlRotation = true;
			CameraBoom->TargetArmLength = 450.0f;
			CameraBoom->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

			PlayerController->bShowMouseCursor = false;
			PlayerController->SetIgnoreLookInput(false);

			FRotator NewControlRotation = GetActorRotation();
			PlayerController->SetControlRotation(NewControlRotation);
		}

		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);		
	}

	if (HasAuthority())
	{	
		// GetCharacterMovement()->MaxWalkSpeed /= HeroAttributeComponent->Status.GroundSpeedRate;
		// HeroAttributeComponent->Status.GroundSpeedRate /= 4.0f;
	}
}