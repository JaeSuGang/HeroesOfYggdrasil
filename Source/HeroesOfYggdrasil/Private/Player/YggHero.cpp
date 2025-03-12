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


AYggHero::AYggHero()
{
	HeroAttributeComponent = CreateDefaultSubobject<UHeroAttributeComponent>(TEXT("AttributeComponent"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetMesh());
	

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

	// 폰 입력 UEnhancedInputComponent 으로 변경
	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();
}

void AYggHero::ToggleAimMode_Implementation()
{
	bAimMode = !bAimMode;

	SetAimMode_Implementation(bAimMode);
}

void AYggHero::SetAimMode_Implementation(bool Value)
{
	bAimMode = Value;
	bUseControllerRotationYaw = bAimMode;

	AMainGameHUD* MainGameHUD = Cast<AMainGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	MainGameHUD->EnableCrossHair(bAimMode);

	if (bUseControllerRotationYaw)
	{
		CameraBoom->TargetArmLength = 200.0f;
		CameraBoom->SocketOffset = FVector(0.0f, 45.0f, 150.0f);
	}
	else {
		CameraBoom->TargetArmLength = 450.0f;
		CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 200.0f);
	}
}

void AYggHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AYggHero::SetCamera_Implementation(FVector NewCameraLocation, FRotator NewCameraRotation, float NewArmLength, FVector NewSocketOffset)
{
	// 시작 카메라 저장.
	StartCameraLocation = NewCameraLocation;
	StartCameraRotation = NewCameraRotation;
	StartArmLength = NewArmLength;
	StartSocketOffset = NewSocketOffset;

	// 플레이 카메라.
	TargetArmLength = 450.0f;
	TargetSocketOffset = FVector(0.0f, 0.0f, 200.0f);
	TargetCameraLocation = StartCameraLocation;
	TargetCameraRotation = FRotator(StartCameraRotation.Pitch, StartCameraRotation.Yaw + 180.0f, StartCameraRotation.Roll);

	bIsCameraTransitioning = true;
	TransitionAlpha = 0.0f;
}

void AYggHero::StartGameCamera(float DeltaTime)
{
	if (bIsCameraTransitioning)
	{
		if (AYggPlayerController* PC = GetController<AYggPlayerController>())
		{
			PC->SetInputEnabled(false);
		}

		TransitionAlpha += DeltaTime * TransitionSpeed;
		TransitionAlpha = FMath::Clamp(TransitionAlpha, 0.0f, 1.0f);

		CameraBoom->TargetArmLength = FMath::Lerp(StartArmLength, TargetArmLength, TransitionAlpha);
		CameraBoom->SocketOffset = FMath::Lerp(StartSocketOffset, TargetSocketOffset, TransitionAlpha);
		CameraBoom->SetWorldLocationAndRotation(
			FMath::Lerp(StartCameraLocation, TargetCameraLocation, TransitionAlpha),
			FMath::Lerp(StartCameraRotation, TargetCameraRotation, TransitionAlpha)
		);

		if (APlayerController* MyController = GetWorld()->GetFirstPlayerController())
		{
			FRotator NewRotation = FMath::Lerp(
				StartCameraRotation,
				TargetCameraRotation,
				TransitionAlpha
			);
			MyController->SetControlRotation(NewRotation);
		}

		if (TransitionAlpha >= 1.0f)
		{
			bIsCameraTransitioning = false;

			if (AYggPlayerController* PC = GetController<AYggPlayerController>())
			{
				PC->SetInputEnabled(true);
			}
		}
	}
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
		if (ActionMap.Find(FName("ToggleAimMode")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("ToggleAimMode")), ETriggerEvent::Started, this, &AYggHero::ToggleAimMode);
			
		}
		if (ActionMap.Find(FName("MouseWheel")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("MouseWheel")), ETriggerEvent::Triggered, this, &AYggHero::MouseWheel);
		}
		if (ActionMap.Find(FName("UIMode")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("UIMode")), ETriggerEvent::Started, this, &AYggHero::UIModeOn);
			EnhancedInput->BindAction(*ActionMap.Find(FName("UIMode")), ETriggerEvent::Completed, this, &AYggHero::UIModeOff);
		}
	}

}

void AYggHero::Look(const FInputActionValue& Value)
{
	if (GetController()->IsLookInputIgnored()||bIsUIMode)
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
	FVector2D MovementVector = Value.Get<FVector2D>();
	FRotator ControllerRotation = GetControlRotation();

	FRotator YawRotation(0, ControllerRotation.Yaw, 0);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AYggHero::BeginPlay()
{
	Super::BeginPlay();
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance != nullptr)
	{
		HeroAnimInstance = Cast<UYggHeroAnimInstance>(GetMesh()->GetAnimInstance());
	}

	
}

void AYggHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StartGameCamera(DeltaTime);
}



void AYggHero::MouseWheel(const FInputActionValue& Value)
{
	float WheelValue = Value.Get<float>();

	// 마우스 휠 입력이 없으면 리턴
	if (WheelValue == 0.0f)
	{
		return;
	}
	// 현재 SpringArm 길이를 가져옴
	float NewLength = CameraBoom->TargetArmLength + (WheelValue * CameraConst::ZoomSpeed);
	// 최소/최대 줌 제한
	NewLength = FMath::Clamp(NewLength, CameraConst::MinCameraBoomLength, CameraConst::MaxCameraBoomLength);
	// 변경된 길이 적용
	CameraBoom->TargetArmLength = NewLength;
}

void AYggHero::UIModeOn(const FInputActionValue& Value)
{
	bIsUIMode = true;
	HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
}


void AYggHero::UIModeOff(const FInputActionValue& Value)
{
	bIsUIMode = false;
	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotAttackable"));
}

