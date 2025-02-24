// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Test/TestAnimInstance_kjh.h"

void AYggHeroController::BeginPlay()
{
    Super::BeginPlay();

    APawn* MyPawn = GetPawn();
    if (MyPawn)
    {
        Possess(MyPawn);
    }

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }

    HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AYggHeroController::GetGenericTeamId() const
{
    return HeroTeamID;
}

void AYggHeroController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
    if (EnhancedInput)
    {
        if (MoveAction)
        {
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AYggHeroController::Move);
        }
        if (LookAction)
        {
            EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AYggHeroController::Look);
        }
        if (JumpAction)
        {
            EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AYggHeroController::Jump);
        }
        if (AttackAction)
        {
            EnhancedInput->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AYggHeroController::Attack);
        }
        if (SkillQAction)
        {
            EnhancedInput->BindAction(SkillQAction, ETriggerEvent::Triggered, this, &AYggHeroController::SkillQ);
        }
        if (SkillEAction)
        {
            EnhancedInput->BindAction(SkillEAction, ETriggerEvent::Triggered, this, &AYggHeroController::SkillE);
        }
        if (SkillRAction)
        {
            EnhancedInput->BindAction(SkillRAction, ETriggerEvent::Triggered, this, &AYggHeroController::SkillR);
        }
    }
}

void AYggHeroController::Move(const FInputActionValue& _Value)
{
    FVector2D MovementVector = _Value.Get<FVector2D>();

    if (APawn* ControlledPawn = GetPawn())
    {
        FRotator ControllerRotation = GetControlRotation();

        FRotator YawRotation(0, ControllerRotation.Yaw, 0);

        FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
        ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AYggHeroController::Look(const FInputActionValue& _Value)
{
    FVector2D LookAxisVector = _Value.Get<FVector2D>();

    if (APawn* ControlledPawn = GetPawn())
    {
        ControlledPawn->AddControllerYawInput(LookAxisVector.X);
        ControlledPawn->AddControllerPitchInput(-LookAxisVector.Y);
    }
}

void AYggHeroController::Jump(const FInputActionValue& _Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Jump"));
}

void AYggHeroController::Attack(const FInputActionValue& _Value)
{
    if (APawn* ControlledPawn = GetPawn())
    {
        USkeletalMeshComponent* MeshComponent = ControlledPawn->FindComponentByClass<USkeletalMeshComponent>();
        if (MeshComponent)
        {
            UAnimInstance* AnimInstance = MeshComponent->GetAnimInstance();
            if (AnimInstance)
            {
                UTestAnimInstance_kjh* TestAnimInstance = Cast<UTestAnimInstance_kjh>(AnimInstance);
                if (TestAnimInstance)
                {
                    TestAnimInstance->SetIsAttacking(true);
                }
            }
        }
    }
}

void AYggHeroController::SkillQ(const FInputActionValue& _Value)
{
    UE_LOG(LogTemp, Warning, TEXT("SkillQ"));
}

void AYggHeroController::SkillE(const FInputActionValue& _Value)
{
    UE_LOG(LogTemp, Warning, TEXT("SkillE"));
}

void AYggHeroController::SkillR(const FInputActionValue& _Value)
{
    UE_LOG(LogTemp, Warning, TEXT("SkillR"));
}
