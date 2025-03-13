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
	}
}

void AYggHeroGreystone::ServerAttack_Implementation()
{
	Attack(FInputActionValue());
}

void AYggHeroGreystone::MulticastAttack_Implementation(int ServerAttackIndex)
{
	CurAttackIndex = ServerAttackIndex;
	
<<<<<<< Updated upstream
	FName MontageName = *FString::Printf(TEXT("Attack%d"), CurAttackIndex);
	
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.Buff.FastAttackSpeed")))
	{
		MontageName = *FString::Printf(TEXT("FAttack%d"), CurAttackIndex);
	}
	
	 PlayMontage(MontageName);
=======
	FName MontageName = *FString::Printf(TEXT("Attack"));

	HeroAnimInstance->PlayMontage(MontageName);
>>>>>>> Stashed changes
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
	FName MontageName = TEXT("SkillE");
	PlayMontage(MontageName);
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
<<<<<<< Updated upstream
	PlayMontage(MontageName);
=======
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
			CameraBoom->TargetArmLength = 700.0f;
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
		GetCharacterMovement()->MaxWalkSpeed /= HeroAttributeComponent->Status->GroundSpeedRate;
		HeroAttributeComponent->Status->GroundSpeedRate /= 4.0f;
	}
>>>>>>> Stashed changes
}