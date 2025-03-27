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

	// Attribute
	HeroAttributeComponent = CreateDefaultSubobject<UHeroAttributeComponent>(TEXT("AttributeComponent"));

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

}

void AYggHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StartGameCamera(DeltaTime);
	if (bAimMode)
	{
		AimRaycast(Cast<APlayerController>(GetController()));
	}
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

void AYggHero::SetCamera_Implementation(FVector NewCameraLocation, FRotator NewCameraRotation, float NewArmLength, FVector NewSocketOffset)
{
	// 시작 카메라 저장.
	StartCameraLocation = NewCameraLocation;
	StartCameraRotation = NewCameraRotation;
	StartArmLength = NewArmLength;
	StartSocketOffset = NewSocketOffset;

	// 플레이 카메라.
	TargetArmLength = 700.0f;
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

// 레이캐스트
void AYggHero::AimRaycast(APlayerController* PlayerController)
{
	if (!PlayerController) return;

	int32 ScreenX, ScreenY;
	PlayerController->GetViewportSize(ScreenX, ScreenY); // 화면 크기 가져오기

	FVector WorldLocation; 
	FVector WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(
		ScreenX * 0.5f, ScreenY * 0.5f,  // 화면 중앙 좌표
		WorldLocation, WorldDirection   // 월드 위치, 월드 방향
	);

	FVector Start = PlayerController->PlayerCameraManager->GetCameraLocation(); // 카메라 위치
	FVector End = WorldLocation + (WorldDirection * 1000.0f); // 에임이 가리키는 3D 위치

	DrawDebugLine(GetWorld(), WorldLocation, End, FColor::Red, false, 0.1f, 0, 1.0f);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(PlayerController->GetPawn()); // 플레이어 캐릭터는 무시

	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}
	bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		TraceParams
	);

	if (bHit == true)
	{
		AActor* HitActor = HitResult.GetActor();
		GEngine->AddOnScreenDebugMessage(
			1,  
			2.0f, 
			FColor::Red, 
			FString::Printf(TEXT("Hit Actor: %s"), *HitActor->GetName()) 
		);
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


void AYggHero::CameraZoomInOut(const FInputActionValue& Value)
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





