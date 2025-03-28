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

	// 닉네임
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());


	FaceCaptureComponent = CreateDefaultSubobject<UCaptureComponent>(TEXT("StatusCamera"));
	FaceCaptureComponent->SetupAttachment(RootComponent);
	FaceCaptureComponent->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	
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

void AYggHero::BeginPlay()
{
	Super::BeginPlay();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	
	if (AnimInstance != nullptr)
	{
		HeroAnimInstance = Cast<UYggHeroAnimInstance>(GetMesh()->GetAnimInstance());
	}

	if (HasAuthority())
	{
		HeroAttributeComponent->ServerDelegate_OnTakeDamage.AddDynamic(this, &AYggHero::TakeDamageEffect);

	}

	if (FaceCaptureComponent)
	{
		FaceCaptureComponent->SetupFaceCapture(this);
	}
	CameraBoom->TargetArmLength = 700.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 200.0f);

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

void AYggHero::TakeDamageEffect_Implementation(float Att)
{
	// 피 튀기는 파티클 재생. 등등.

}

void AYggHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AYggHero, HeroAttributeComponent);
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
		if (ActionMap.Contains(FName("Roll")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Roll")], ETriggerEvent::Started, this, &AYggHero::Roll);
		}
		if (ActionMap.Find(FName("ToggleAimMode")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("ToggleAimMode")], ETriggerEvent::Started, this, &AYggHero::ToggleAimMode);
		}
		if (ActionMap.Find(FName("CameraZoomInOut")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("CameraZoomInOut")], ETriggerEvent::Triggered, this, &AYggHero::CameraZoomInOut);
		}
		if (ActionMap.Find(FName("ToggleUIMode")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("ToggleUIMode")], ETriggerEvent::Started, this, &AYggHero::ToggleUIMode);
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
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable"))) return;

	if (HasAuthority())
	{
		MulticastRoll(Value);
	}
	else
	{
		ServerRoll(Value);
	}
}

void AYggHero::ServerRoll_Implementation(const FInputActionValue& Value)
{
	Roll(Value);
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

void AYggHero::ToggleUIMode()
{
	SetUIMode(!bIsUIMode);
}

void AYggHero::SetUIMode(bool Value)
{
	bIsUIMode = Value;
	if (bIsUIMode)
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
	}
	else
	{
		HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotAttackable"));
	}
}





