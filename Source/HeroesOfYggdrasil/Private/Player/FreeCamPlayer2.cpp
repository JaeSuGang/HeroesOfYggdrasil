// Coded By AssortRock Unreal Engine Class Project


#include "Player/FreeCamPlayer2.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AFreeCamPlayer2::AFreeCamPlayer2(const FObjectInitializer& objectInitializer)
	:
	Super(objectInitializer)
{
	/*  */
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	
	GetCapsuleComponent()->SetEnableGravity(false);
	GetMesh()->SetEnableGravity(false);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetEnableGravity(false);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 0.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

void AFreeCamPlayer2::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay %s, HasAuthority=%d"), *GetName(), HasAuthority());

	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}

void AFreeCamPlayer2::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("fdas : %d"), static_cast<int>(GetCharacterMovement()->MovementMode));
}

void AFreeCamPlayer2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFreeCamPlayer2::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFreeCamPlayer2::Look);
	}
}

void AFreeCamPlayer2::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();

		const FVector ForwardDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AFreeCamPlayer2::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}