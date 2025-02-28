// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHero.h"

#include "Engine/LocalPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"

#include "GameFramework/SpringArmComponent.h"

#include "MainGame/MainGameHUD.h"
#include "Kismet/GameplayStatics.h"

AYggHero::AYggHero()
{
	// 카메라에 따라 돌게 세팅할꺼면 Yaw=true로
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// 2개 옵션 서로 반대
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;


	// 카메라 
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	// 이거 2개는 회의 ㄱㄱ
	CameraBoom->TargetArmLength = 450.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 300.0f);

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
		CameraBoom->SocketOffset = FVector(0.0f, 45.0f, 250.0f);
	}
	else {
		CameraBoom->TargetArmLength = 450.0f;
		CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 300.0f);
	}
}

void AYggHero::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYggHero, bAimMode);
}

void AYggHero::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	FRotator CurrentRotation = GetControlRotation();

	float ClampedPitch = FMath::ClampAngle(CurrentRotation.Pitch + LookAxisVector.Y, -40.0f, 60.0f);

	GetController()->SetControlRotation(FRotator(ClampedPitch, CurrentRotation.Yaw, CurrentRotation.Roll));

	AddControllerYawInput(LookAxisVector.X);

//	AddControllerPitchInput(-LookAxisVector.Y);
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

	// ??? Yaw에 180.0f 을 추가 해야하는 이유?
	FollowCamera->SetWorldRotation(FRotator(-25.0f, 180.0f, 0.0f));		
}

void AYggHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}