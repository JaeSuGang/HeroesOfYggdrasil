// Coded By AssortRock Unreal Engine Class Project

// Project Headers
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

//  Project Headers : UI
#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/UI/YggMainGameUserWidget.h"
#include "MainGame/UI/YggCastingBarUserWidget.h"

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
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("Attack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh(), TEXT("sword_bottom"));
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("Attack"), AttackCapsuleComponent);
	} 
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillQAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillQAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillEAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillEAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillRAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillRAttack"), AttackCapsuleComponent);
	}
}

AYggHeroGreystone::~AYggHeroGreystone()
{
}

void AYggHeroGreystone::BeginPlay()
{
	Super::BeginPlay();

	if (ActionMap.IsEmpty()) return;
	ActionMap.Remove(FName("Jump"));

	if (!HeroAttributeComponent) return;
	HeroAttributeComponent->ServerSetBaseData_Implementation(TEXT("Greystone"));
	//UpdateStatus();	
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
		if (ActionMap.Find(FName("Roll")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Roll")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Roll);
		}
		if (ActionMap.Find(FName("Attack")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Started, this, &AYggHeroGreystone::Attack);
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Completed, this, &AYggHeroGreystone::EndAttack);
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
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotMoveable"))) return;

	Super::Move(Value);
}

void AYggHeroGreystone::Attack(const FInputActionValue& Value)
{
	if (bIsSkillR && !(HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))))
	{
		RFall();
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MagicCircleOff();
		return;
	}

	Super::Attack(Value);		
}

void AYggHeroGreystone::EndAttack(const FInputActionValue& Value)
{
	HeroAttributeComponent->RemoveTag(TEXT("Character.State.PressedAttack"));
}

void AYggHeroGreystone::SkillQ(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))) return;
	if (HeroAttributeComponent->SkillQCurCoolTime > 0.0f) return;

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
	MulticastSkillQ();
}

void AYggHeroGreystone::MulticastSkillQ_Implementation()
{
	FName MontageName = TEXT("SkillQ");
	HeroAnimInstance->PlayMontage(MontageName);

	HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
	HeroAttributeComponent->SkillQCurCoolTime = HeroAttributeComponent->SkillQMaxCoolTime;
}

void AYggHeroGreystone::SkillE(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))) return;
	if (HeroAttributeComponent->SkillECurCoolTime > 0.0f) return;

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
	MulticastSkillE();
}

void AYggHeroGreystone::MulticastSkillE_Implementation()
{
	FName MontageName = TEXT("SkillE");
	HeroAnimInstance->PlayMontage(MontageName);

	HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
	HeroAttributeComponent->SkillECurCoolTime = HeroAttributeComponent->SkillEMaxCoolTime;
}

void AYggHeroGreystone::SkillR(const FInputActionValue& Value)
{
	if (bIsSkillR) return;

	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))) return;	
	if (HeroAttributeComponent->SkillRCurCoolTime > 0.0f) return;

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
	MulticastSkillR();
}

void AYggHeroGreystone::MulticastSkillR_Implementation()
{
	FName MontageName = TEXT("SkillR");
	HeroAnimInstance->PlayMontage(MontageName);

	HeroAttributeComponent->SkillRCurCoolTime = HeroAttributeComponent->SkillRMaxCoolTime;
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
	
	UAnimMontage* CurrentMontage = HeroAnimInstance->GetCurrentActiveMontage();
	HeroAnimInstance->Montage_Resume(CurrentMontage);
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

	OnSkillCastEnd.Broadcast();

	if (IsValid(SkillRDecal))
	{
		SetActorLocation(SkillRDecal->GetComponentLocation());

		SkillRDecal->DestroyComponent();
		SkillRDecal = nullptr;
		
		if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
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
		// GetCharacterMovement()->MaxWalkSpeed /= HeroAttributeComponent->Status.GroundSpeedRate;
		// HeroAttributeComponent->Status.GroundSpeedRate /= 4.0f;
	}
}