// Coded By AssortRock Unreal Engine Class Project


#include "Actors/AuroraOrb.h"

// Sets default values
AAuroraOrb::AAuroraOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAuroraOrb::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        FRotator ControlRotation = PC->GetControlRotation();
        MoveDirection = ControlRotation.Vector();
    }

    FTimerHandle OrbTimer;
    GetWorld()->GetTimerManager().SetTimer(OrbTimer, [this]() {
        this->Destroy();
    }
    , 3.0f, false);
}

// Called every frame
void AAuroraOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!MoveDirection.IsZero())
    {
        FVector NewLoc = GetActorLocation() + MoveDirection * MoveSpeed * DeltaTime;
        SetActorLocation(NewLoc);
    }
}

