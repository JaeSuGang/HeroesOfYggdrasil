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

#include "GameFramework/SpringArmComponent.h"


AYggHero::AYggHero()
{
	// 카메라에 따라 돌게 세팅
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;


	// 카메라 
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpring"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->TargetArmLength = 450.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 300.0f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	// 폰 입력 UEnhancedInputComponent 으로 변경
	OverrideInputComponentClass = UEnhancedInputComponent::StaticClass();
}

void AYggHero::Look(const FInputActionValue& _Value)
{
	FVector2D LookAxisVector = _Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(-LookAxisVector.Y);
}

void AYggHero::Move(const FInputActionValue& _Value)
{

	FVector2D MovementVector = _Value.Get<FVector2D>();
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

	UE_LOG(LogTemp, Warning, TEXT("CameraBoom Rotation: %s"), *CameraBoom->GetComponentRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("FollowCamera Rotation: %s"), *FollowCamera->GetComponentRotation().ToString());
}
