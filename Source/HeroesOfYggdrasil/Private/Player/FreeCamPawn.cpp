// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FreeCamPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Attribute/AttributeComponent.h"

AFreeCamPawn::AFreeCamPawn(const FObjectInitializer& objectInitializer)
{
	/* Default 값 */
	bUseControllerRotationRoll = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	/* 컴포넌트 */
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->bOwnerNoSee = true;
	RootComponent = MeshComponent;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 0.0f;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComp"));


}

void AFreeCamPawn::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(DefaultInputMappingContext, 0);
		}
	}
}

void AFreeCamPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFreeCamPawn::Look);
}

void AFreeCamPawn::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
