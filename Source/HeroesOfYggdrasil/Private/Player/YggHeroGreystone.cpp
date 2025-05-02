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
	AttackCapsuleComponentMap.Reset();

	NormalAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("Attack"));
	NormalAttackCapsuleComponent->SetupAttachment(GetMesh());
	NormalAttackCapsuleComponent->SetOwnerCharacter(this);
	AttackCapsuleComponentMap.Add(TEXT("Attack"), NormalAttackCapsuleComponent);
	
	SkillQAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillQAttack"));
	SkillQAttackCapsuleComponent->SetupAttachment(GetMesh());
	SkillQAttackCapsuleComponent->SetOwnerCharacter(this);
	AttackCapsuleComponentMap.Add(TEXT("SkillQAttack"), SkillQAttackCapsuleComponent);
		
	SkillEAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillEAttack"));
	SkillEAttackCapsuleComponent->SetupAttachment(GetMesh());
	SkillEAttackCapsuleComponent->SetOwnerCharacter(this);
	AttackCapsuleComponentMap.Add(TEXT("SkillEAttack"), SkillEAttackCapsuleComponent);
	
	SkillRAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillRAttack"));
	SkillRAttackCapsuleComponent->SetupAttachment(GetMesh());
	SkillRAttackCapsuleComponent->SetOwnerCharacter(this);
	AttackCapsuleComponentMap.Add(TEXT("SkillRAttack"), SkillRAttackCapsuleComponent);
	

	SkillRBuffCapsule = CreateDefaultSubobject<UYggCapsuleComponent>(TEXT("SkillRRecover"));
	SkillRBuffCapsule->SetupAttachment(GetMesh());
	SkillRBuffCapsule->SetOwnerCharacter(this);
	
	SkillRBuffCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SkillRBuffCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);
	SkillRBuffCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECR_Overlap);
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

	GetCharacterMovement()->AirControl = 0.5f;
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

	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));

	if (HasAuthority())
	{
		DoSkillQLeap();
		MulticastSkillQ();
	}
	else
	{
		Server_DoSkillQLeap();
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
		// HeroAttributeComponent->Server_SetMaxMoveSpeed(HeroAttributeComponent->MaxMoveSpeed * 3.0f);
		
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
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECR_Ignore);

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
	if (!IsLocallyControlled()) return;

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

		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
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
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECR_Block);
	}

	if (HasAuthority())
	{
		// HeroAttributeComponent->Server_SetMaxMoveSpeed(HeroAttributeComponent->MaxMoveSpeed / 3.0f);
	}
}

void AYggHeroGreystone::Server_DoSkillQLeap_Implementation()
{
	DoSkillQLeap();
}

void AYggHeroGreystone::DoSkillQLeap()
{
	// 1. 도약 물리 파라미터 설정
	const float LeapPower = GetHeroAttributeComponent()->MaxMoveSpeed * 1.5f;
	const float VerticalBoost = 100.f; // 수직 도약 힘
	FVector LeapDirection = GetActorForwardVector() + FVector(0, 0, 0.5f); // 45도 각도

	// 2. 캐릭터 회전 보정
	FRotator NewRotation = LeapDirection.Rotation();
	NewRotation.Pitch = 0; // 수직 회전 제거
	SetActorRotation(NewRotation);

	// 3. 물리 기반 도약 실행
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		// 현재 속도 초기화
		MoveComp->Velocity = FVector::ZeroVector;

		// LaunchCharacter를 사용한 물리 도약
		LaunchCharacter(
			LeapDirection * LeapPower + FVector(0, 0, VerticalBoost),
			false, // 수평 속도 유지
			false  // 수직 속도 유지
		);

		// 도약 중 회전 고정
		MoveComp->bOrientRotationToMovement = false;

		FTimerHandle RotationResetHandle;
		// 0.5초 후 회전 기능 복구
		GetWorld()->GetTimerManager().SetTimer(
			RotationResetHandle,
			[MoveComp]() { MoveComp->bOrientRotationToMovement = true; },
			0.5f,
			false
		);
	}
}