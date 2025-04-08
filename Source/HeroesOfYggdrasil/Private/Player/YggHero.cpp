// Coded By AssortRock Unreal Engine Class Project

#include "Player/YggHero.h"

// Unreal Engine Core
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"

// Camera & Movement
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/CaptureComponent.h"

// Input
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Game Framework
#include "GameFramework/Controller.h"
#include "Core/YggPlayerController.h"
#include "Attribute/AttributeComponent.h"

// Network
#include "Net/UnrealNetwork.h"

// HUD
#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/UI/YggMiniMapIconActor.h"

// Tag
#include "Attribute/HeroAttributeComponent.h"

// Animation
#include "Animation/YggHeroAnimInstance.h"

#include "MainGame/UI/YggNicknameBarUserWidget.h"
#include "Components/WidgetComponent.h"

// Data
#include "Data/YggConst.h"

#include "Data/YggStructData.h"




AYggHero::AYggHero()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// 카메라 
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;


	HeroAttributeComponent = CreateDefaultSubobject<UHeroAttributeComponent>(TEXT("HeroAttributeComponent"));
	CharacterAttributeComponent = Cast<UCharacterAttributeComponent>(HeroAttributeComponent);

	// 닉네임
	NickNameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	NickNameWidgetComponent->SetupAttachment(GetMesh());

	FaceCaptureComponent = CreateDefaultSubobject<UCaptureComponent>(TEXT("StatusCamera"));
	FaceCaptureComponent->SetupAttachment(RootComponent);
	FaceCaptureComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	MiniMapCaptureComponent = CreateDefaultSubobject<UCaptureComponent>(TEXT("MiniMapCamera"));
	MiniMapCaptureComponent->SetupAttachment(RootComponent);
	MiniMapCaptureComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	MiniMapCaptureComponent->AddRelativeLocation(FVector(0.0f, 0.0f, 1000.0f));
	MiniMapCaptureComponent->OrthoWidth = 1000.0f;

	// 폰 입력 UEnhancedInputComponent 으로 변경
	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();

	// IA
	ActionMap.Add(TEXT("Move"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("Look"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("Jump"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("Attack"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("SkillQ"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("SkillE"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("SkillR"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("Roll"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("ToggleUIMode"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("ToggleAimMode"), NewObject<UInputAction>());
	ActionMap.Add(TEXT("CameraZoomInOut"), NewObject<UInputAction>());
}

UCharacterAttributeComponent* AYggHero::GetAttributeComponent()
{
	return HeroAttributeComponent;
}

void AYggHero::BeginPlay()
{
	Super::BeginPlay();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	HeroAttributeComponent->AddTag(TEXT("Character"));

	if (AnimInstance != nullptr)
	{
		HeroAnimInstance = Cast<UYggHeroAnimInstance>(GetMesh()->GetAnimInstance());
	}

	if (HasAuthority())
	{
		HeroAttributeComponent->ServerDelegate_OnTakeDamage.AddDynamic(this, &AYggHero::TakeDamageEffect);
		HeroAttributeComponent->ServerDelegate_OnTakeDamage.AddDynamic(this, &AYggHero::Die);
	}

	if (FaceCaptureComponent)
	{
		FaceCaptureComponent->SetupFaceCapture(this);
	}

	HeroAttributeComponent->AddTag(TEXT("Character"));

	AYggMiniMapIconActor* MiniMapIcon = GetWorld()->SpawnActor<AYggMiniMapIconActor>(MiniMapIconClass);
	MiniMapIcon->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	MiniMapIcon->SetPaperSprite(FName("Character"));
	MiniMapIcon->SetAttachedCharacter(this);
	MiniMapCaptureComponent->SetupMiniMapCapture(MiniMapIcon);

	CameraBoom->TargetArmLength = 700.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 200.0f);

	FName MontageName = *FString::Printf(TEXT("LevelStart"));
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AYggHero::ToggleAimMode()
{
	SetAimMode(!bAimMode);
}

void AYggHero::SetAimMode(bool Value)
{
	bAimMode = Value;
	bUseControllerRotationYaw = bAimMode;

	AMainGameHUD* MainGameHUD = Cast<AMainGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MainGameHUD->EnableCrossHair(bAimMode);

	if (bUseControllerRotationYaw)
	{
		CameraBoom->TargetArmLength = 150.0f;
		CameraBoom->SocketOffset = FVector(0.0f, 45.0f, 75.0f);
	}
	else {
		CameraBoom->TargetArmLength = 700.0f;
		CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 200.0f);
	}
}

void AYggHero::UpdateStatus()
{
	GetCharacterMovement()->MaxWalkSpeed = HeroAttributeComponent->MaxMoveSpeed;
	GetCharacterMovement()->JumpZVelocity = HeroAttributeComponent->JumpPower;
}

//void AYggHero::ServerDie_Implementation(float Delegate)
//{
//	if (HeroAttributeComponent->HP <= 0.0f)
//	{
//		MulticastDie();
//	}
//}
//
//void AYggHero::MulticastDie_Implementation()
//{
//	if (HeroAttributeComponent->HP <= 0.0f && !bIsDeath)
//	{
//		FName MontageName = *FString::Printf(TEXT("Death"));
//		HeroAnimInstance->PlayMontage(MontageName);
//	
//		bIsDeath = true;
//
//		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
//		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
//		HeroAttributeComponent->AddTag(TEXT("Character.State.NotRollable"));
//	}
//}

void AYggHero::TakeDamageEffect_Implementation(float Att)
{
	// 피 튀기는 파티클 재생. 등등.

}

void AYggHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AYggHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		if (ActionMap.Contains(FName("Move")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Move")], ETriggerEvent::Triggered, this, &AYggHero::Move);
		}
		if (ActionMap.Contains(FName("Look")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Look")], ETriggerEvent::Triggered, this, &AYggHero::Look);
		}
		if (ActionMap.Contains(FName("Jump")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Jump")], ETriggerEvent::Triggered, this, &AYggHero::Jump);
		}
		if (ActionMap.Contains(FName("Attack")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Triggered, this, &AYggHero::Attack);
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Completed, this, &AYggHero::EndAttack);
		}
		if (ActionMap.Contains(FName("Roll")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Roll")], ETriggerEvent::Started, this, &AYggHero::Roll);
		}
		if (ActionMap.Contains(FName("SkillQ")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillQ")], ETriggerEvent::Started, this, &AYggHero::SkillQ);
		}
		if (ActionMap.Contains(FName("SkillE")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillE")], ETriggerEvent::Started, this, &AYggHero::SkillE);
		}
		if (ActionMap.Contains(FName("SkillR")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillR")], ETriggerEvent::Started, this, &AYggHero::SkillR);
		}

		if (ActionMap.Find(FName("CameraZoomInOut")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("CameraZoomInOut")], ETriggerEvent::Triggered, this, &AYggHero::CameraZoomInOut);
		}
	}
}

void AYggHero::Look(const FInputActionValue& Value)
{
	if (GetController()->IsLookInputIgnored() || bIsUIMode)
	{
		return;
	}
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	FRotator CurrentRotation = GetControlRotation();
	float ClampedPitch = FMath::ClampAngle(CurrentRotation.Pitch + LookAxisVector.Y, -40.0f, 60.0f);
	GetController()->SetControlRotation(FRotator(ClampedPitch, CurrentRotation.Yaw, CurrentRotation.Roll));
	AddControllerYawInput(LookAxisVector.X);
}

void AYggHero::Move(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotMoveable")))
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

void AYggHero::Jump()
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotMoveable")))
	{
		return;
	}
	Super::Jump();
}

void AYggHero::Roll(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotRollable"))) return;
	if (HeroAttributeComponent->CurRollCount <= 0) return;

	if (HasAuthority())
	{
		HeroAttributeComponent->CurRollCount -= 1;
		MulticastRoll(Value);
	}
	else
	{
		ServerRoll(Value);
	}
}

void AYggHero::ServerRoll_Implementation(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotRollable"))) return;
	if (HeroAttributeComponent->CurRollCount <= 0) return;
	HeroAttributeComponent->CurRollCount -= 1;

	MulticastRoll(Value);
}

void AYggHero::MulticastRoll_Implementation(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotMoveable"))) return;
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotRollable"))) return;

	HeroAttributeComponent->AddTag(TEXT("Character.State.NotRollable"));
	HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
	HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));

	FName MontageName = *FString::Printf(TEXT("Roll"));
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHero::Attack(const FInputActionValue& Value)
{
	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.PressedAttack")))
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.PressedAttack"));
	}
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastAttack(Value);
	}
	else
	{
		ServerAttack(Value);
		return;
	}
}

void AYggHero::ServerAttack_Implementation(const FInputActionValue& Value)
{
	Attack(FInputActionValue());
}

void AYggHero::MulticastAttack_Implementation(const FInputActionValue& Value)
{
	FName MontageName = *FString::Printf(TEXT("Attack"));

	HeroAnimInstance->PlayMontage(MontageName);
}
void AYggHero::EndAttack(const FInputActionValue& Value)
{
	HeroAttributeComponent->RemoveTag(TEXT("Character.State.PressedAttack"));
}


void AYggHero::SkillQ(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		MulticastHeroSkillQ(Value);
	}
	else
	{
		ServerHeroSkillQ(Value);
	}

	float CoolTime = HeroAttributeComponent->SkillQMaxCoolTime;
	OnSkillQ.Broadcast(FName("SkillQ"), CoolTime);
}
void AYggHero::ServerHeroSkillQ_Implementation(const FInputActionValue& Value)
{
	SkillQ(Value);
}
void AYggHero::MulticastHeroSkillQ_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillQ");
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHero::SkillE(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		MulticastHeroSkillE(Value);
	}
	else
	{
		ServerHeroSkillE(Value);
	}

	float CoolTime = HeroAttributeComponent->SkillEMaxCoolTime;
	OnSkillE.Broadcast(FName("SkillE"), CoolTime);
}

void AYggHero::ServerHeroSkillE_Implementation(const FInputActionValue& Value)
{
	SkillE(Value);
}

void AYggHero::MulticastHeroSkillE_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillE");
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHero::SkillR(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		MulticastHeroSkillR(Value);
	}
	else
	{
		ServerHeroSkillR(Value);
	}

	float CoolTime = HeroAttributeComponent->SkillRMaxCoolTime;
	OnSkillR.Broadcast(FName("SkillR"), CoolTime);
}

void AYggHero::ServerHeroSkillR_Implementation(const FInputActionValue& Value)
{
	SkillR(Value);
}

void AYggHero::MulticastHeroSkillR_Implementation(const FInputActionValue& Value)
{
	FName MontageName = TEXT("SkillR");
	HeroAnimInstance->PlayMontage(MontageName);
}

void AYggHero::Die(float Delegate)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.Death"))) return;
	if (HeroAttributeComponent->HP > 0.0f) return;
		
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotRollable"));
		HeroAttributeComponent->AddTag(TEXT("Character.State.Death"));
		MulticastDie(Delegate);
	}
	else
	{
		ServerDie(Delegate);
	}	
}

void AYggHero::ServerDie_Implementation(float Delegate)
{
	Die(Delegate);
}

void AYggHero::MulticastDie_Implementation(float Delegate)
{
	FName MontageName = TEXT("Death");
	HeroAnimInstance->PlayMontage(MontageName);
}



void AYggHero::CameraZoomInOut(const FInputActionValue& Value)
{
	float WheelValue = Value.Get<float>();
	if (WheelValue == 0.0f)
	{
		return;
	}
	float NewLength = CameraBoom->TargetArmLength + (WheelValue * CameraConst::ZoomSpeed);
	NewLength = FMath::Clamp(NewLength, CameraConst::MinCameraBoomLength, CameraConst::MaxCameraBoomLength);
	CameraBoom->TargetArmLength = NewLength;
}

