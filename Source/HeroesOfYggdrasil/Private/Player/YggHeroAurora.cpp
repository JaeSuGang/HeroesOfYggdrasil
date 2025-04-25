// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroAurora.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Input System Modules
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Animation/YggHeroAnimInstance.h"

#include "Kismet/GameplayStatics.h"

#include "Actors/AuroraFrostCatalyst.h"

AYggHeroAurora::AYggHeroAurora()
{
	AttackCapsuleComponentMap.Reset();
		
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

	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.8f;
	GetCharacterMovement()->GravityScale = 1.2f;
	GetCharacterMovement()->BrakingDecelerationFlying = 1000.f;
}

void AYggHeroAurora::BeginPlay()
{
	Super::BeginPlay();

	if (ActionMap.IsEmpty()) return;
	ActionMap.Remove(FName("ToggleAimMode"));
	ActionMap.Remove(FName("CameraZoomInOut"));

	if (!HeroAttributeComponent) return;
	HeroAttributeComponent->ServerSetBaseData_Implementation(TEXT("Aurora"));
	//UpdateStatus();
}

void AYggHeroAurora::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSkillE)
	{
		MagicCircleOn();
	}

	if (bIsJetpacking && CurrentFuel > 0.0f)
	{
		FVector JetForce = FVector::UpVector * JetpackThrust;
		GetCharacterMovement()->AddForce(JetForce * GetCharacterMovement()->Mass);

		// 연료 소모
		CurrentFuel = FMath::Max(CurrentFuel - (FuelConsumptionRate * DeltaTime), 0.0f);

		// 연료 소진 시 강제 종료
		if (CurrentFuel <= 0.0f)
		{
			JetpackOff(FInputActionValue(false));
		}
	}
	else if (!bIsJetpacking && (GetCharacterMovement()->IsMovingOnGround() || CurrentFuel > 0.0f))
	{
		CurrentFuel = FMath::Min(CurrentFuel + (FuelRechargeRate * DeltaTime), MaxJetpackFuel);
	}
}

void AYggHeroAurora::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		if (ActionMap.Contains(FName("Look")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Look")], ETriggerEvent::Triggered, this, &AYggHeroAurora::Look);
		}
		if (ActionMap.Contains(FName("Roll")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Roll")], ETriggerEvent::Started, this, &AYggHeroAurora::Roll);
		}
		if (ActionMap.Contains(FName("Attack")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Triggered, this, &AYggHeroAurora::Attack);
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Completed, this, &AYggHeroAurora::EndAttack);
		}
		if (ActionMap.Contains(FName("Jump")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Jump")], ETriggerEvent::Triggered, this, &AYggHeroAurora::JetpackOn);
			EnhancedInput->BindAction(ActionMap[TEXT("Jump")], ETriggerEvent::Completed, this, &AYggHeroAurora::JetpackOff);
		}
		if (ActionMap.Contains(FName("SkillQ")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillQ")), ETriggerEvent::Triggered, this, &AYggHeroAurora::SkillQ);
		}
		if (ActionMap.Contains(FName("SkillE")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillE")), ETriggerEvent::Triggered, this, &AYggHeroAurora::SkillE);
		}
		if (ActionMap.Contains(FName("SkillR")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillR")), ETriggerEvent::Triggered, this, &AYggHeroAurora::SkillR);
		}
		if (ActionMap.Contains(FName("Roll")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Roll")), ETriggerEvent::Triggered, this, &AYggHeroAurora::Roll);
		}
	}
}

void AYggHeroAurora::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FTimerHandle InitTimer;
	GetWorld()->GetTimerManager().SetTimer(InitTimer, [this]()
	{
		SetAimMode(true);
	}, 2.0f, false);
}

void AYggHeroAurora::Look(const FInputActionValue& Value)
{
	if (GetController()->IsLookInputIgnored() || bIsUIMode)
	{
		return;
	}
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	FRotator CurrentRotation = GetControlRotation();
	float ClampedPitch = FMath::ClampAngle(CurrentRotation.Pitch + LookAxisVector.Y, -70.0f, 60.0f);
	GetController()->SetControlRotation(FRotator(ClampedPitch, CurrentRotation.Yaw, CurrentRotation.Roll));
	AddControllerYawInput(LookAxisVector.X);
}

void AYggHeroAurora::Roll(const FInputActionValue& Value)
{
	if (!GetCharacterMovement()->IsMovingOnGround()) return;

	if (HeroAttributeComponent->CurRollCount <= 0)
	{
		return;
	}
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotRollable")))
	{
		return;
	}
	HeroAttributeComponent->CurRollCount -= 1;
	if (HasAuthority())
	{
		MulticastRoll(Value);
		return;
	}
	else
	{
		ServerRoll(Value);
		return;
	}
}

void AYggHeroAurora::Attack(const FInputActionValue& Value)
{
	if (bIsSkillE)
	{
		bIsSkillE = false;

		MagicCircleOff();

		return;
	}

	Super::Attack(Value);
}

void AYggHeroAurora::EndAttack(const FInputActionValue& Value)
{
	HeroAttributeComponent->RemoveTag(TEXT("Character.State.PressedAttack"));
}

void AYggHeroAurora::SkillQ(const FInputActionValue& Value)
{
	Super::SkillQ(Value);

	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));
	HeroAttributeComponent->AddTag(TEXT("Character.State.NotRollable"));

	float ContinueTime = HeroAttributeComponent->SkillQMaxContinueTime;
	FTimerHandle TimeHandle;
	GetWorld()->GetTimerManager().SetTimer(TimeHandle, [this]()
	{
		if (USkeletalMeshComponent* MeshComp = GetMesh())
		{
			if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
			{
				UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
				if (CurrentMontage)
				{
					float BlendOutTime = 0.25f;
					AnimInstance->Montage_Stop(BlendOutTime, CurrentMontage);
				}
			}
		}

		HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotAttackable"));

	}, ContinueTime + 0.8f, false);
}

void AYggHeroAurora::SkillE(const FInputActionValue& Value)
{
	Super::SkillE(Value);

	bIsSkillE = true;

	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));
}

void AYggHeroAurora::SkillR(const FInputActionValue& Value)
{
	Super::SkillR(Value);

	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));
}

void AYggHeroAurora::Jump()
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotMoveable"))) return;

	Super::Jump();

	if (GetCharacterMovement()->IsFalling())
	{
		JetpackOn(FInputActionValue(true));
	}
}

void AYggHeroAurora::MagicCircleOn()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC || !PC->GetPawn())
		return;

	// 1. 카메라 위치 & 회전 획득
	FVector CameraLoc;
	FRotator CameraRot;
	PC->GetPlayerViewPoint(CameraLoc, CameraRot);

	// 2. 뷰포트 중앙 좌표 계산
	int32 ViewportSizeX, ViewportSizeY;
	PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenCenter(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);

	// 3. 화면 중앙 → 월드 언디파인된 위치 & 방향 변환
	FVector WorldOrigin, WorldDirection;
	PC->DeprojectScreenPositionToWorld(
		ScreenCenter.X,
		ScreenCenter.Y,
		WorldOrigin,
		WorldDirection
	);

	// 4. Line Trace 수행
	const float TraceDistance = 3000.f;
	FVector TraceStart = CameraLoc;
	FVector TraceEnd = TraceStart + WorldDirection * TraceDistance;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		Params
	);

	// 5. TargetPoint 결정
	FVector TargetPoint = bHit ? Hit.ImpactPoint : TraceEnd;
	MagicTargetPoint = TargetPoint;

	// 6. 데칼 스폰 또는 위치 갱신
	if (!IsValid(SkillEDecal))
	{
		SkillEDecal = UGameplayStatics::SpawnDecalAtLocation(
			GetWorld(),
			SkillEDecalMaterial,
			FVector(512.0f),
			TargetPoint,
			FRotator(-90.0f, 0.0f, 0.0f),
			0.f
		);
	}
	else
	{
		SkillEDecal->SetWorldLocation(TargetPoint);
	}
}

void AYggHeroAurora::MagicCircleOff()
{
	bIsSkillE = false;

	OnSkillCastEnd.Broadcast();

	if (IsValid(SkillEDecal))
	{
		SkillEDecal->DestroyComponent();
		SkillEDecal = nullptr;
	}
}

void AYggHeroAurora::JetpackOn(const FInputActionValue& Value)
{
	// 공중에 있고 연료가 남았을 때만 작동
	if (GetCharacterMovement()->IsFalling() && CurrentFuel > 0.0f)
	{
		bIsJetpacking = true;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
	// 지면에서 첫 점프
	else if (GetCharacterMovement()->IsMovingOnGround())
	{
		Super::Jump();
	}
}

void AYggHeroAurora::JetpackOff(const FInputActionValue& Value)
{
	bIsJetpacking = false;
	if (GetCharacterMovement()->MovementMode == MOVE_Flying)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	}
}