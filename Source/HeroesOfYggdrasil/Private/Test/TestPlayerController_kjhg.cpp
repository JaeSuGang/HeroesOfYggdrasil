// Coded By AssortRock Unreal Engine Class Project


#include "Test/TestPlayerController_kjhg.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Test/TestAnimInstance_kjh.h"

void ATestPlayerController_kjhg::BeginPlay()
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


}

void ATestPlayerController_kjhg::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
    if (EnhancedInput)
    {
        if (MoveAction)
        {
            EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestPlayerController_kjhg::Move);
        }
        if (LookAction)
        {
            EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestPlayerController_kjhg::Look);
        }
        if (JumpAction)
        {
            EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ATestPlayerController_kjhg::Jump);
        }
        if (AttackAction)
        {
            EnhancedInput->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATestPlayerController_kjhg::Attack);
        }
        if (SkillQAction)
        {
            EnhancedInput->BindAction(SkillQAction, ETriggerEvent::Triggered, this, &ATestPlayerController_kjhg::SkillQ);
        }
        if (SkillEAction)
        {
            EnhancedInput->BindAction(SkillEAction, ETriggerEvent::Triggered, this, &ATestPlayerController_kjhg::SkillE);
        } 
        if (SkillRAction)
        {
            EnhancedInput->BindAction(SkillRAction, ETriggerEvent::Triggered, this, &ATestPlayerController_kjhg::SkillR);
        }
    }
}

void ATestPlayerController_kjhg::Move(const FInputActionValue& _Value)
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

void ATestPlayerController_kjhg::Look(const FInputActionValue& _Value)
{
    FVector2D LookAxisVector = _Value.Get<FVector2D>();

    if (APawn* ControlledPawn = GetPawn())
    {
        ControlledPawn->AddControllerYawInput(LookAxisVector.X);
        ControlledPawn->AddControllerPitchInput(-LookAxisVector.Y);
    }
}

void ATestPlayerController_kjhg::Jump(const FInputActionValue& _Value)
{  
    UE_LOG(LogTemp, Warning, TEXT("Jump"));
}

void ATestPlayerController_kjhg::Attack(const FInputActionValue& _Value)
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

void ATestPlayerController_kjhg::SkillQ(const FInputActionValue& _Value)
{
    UE_LOG(LogTemp, Warning, TEXT("SkillQ"));
}

void ATestPlayerController_kjhg::SkillE(const FInputActionValue& _Value)
{
    UE_LOG(LogTemp, Warning, TEXT("SkillE"));
}

void ATestPlayerController_kjhg::SkillR(const FInputActionValue& _Value)
{
    UE_LOG(LogTemp, Warning, TEXT("SkillR"));
}
