// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FreeCamPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Attribute/AttributeComponent.h"

AFreeCamPawn::AFreeCamPawn(const FObjectInitializer& objectInitializer)
{
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComp"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	RootComponent = MeshComponent;

	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent->SetupAttachment(SpringArmComponent);
}
