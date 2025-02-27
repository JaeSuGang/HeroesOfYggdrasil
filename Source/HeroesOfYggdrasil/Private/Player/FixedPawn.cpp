// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FixedPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Attribute/AttributeComponent.h"

AFixedPawn::AFixedPawn(const FObjectInitializer& objectInitializer)
{
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComp"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));

	RootComponent = MeshComponent;

	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent->SetupAttachment(SpringArmComponent);

	SplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AFixedPawn::FollowSplineToHero()
{

}