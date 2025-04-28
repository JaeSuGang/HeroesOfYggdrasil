// Coded By AssortRock Unreal Engine Class Project


#include "Actors/AuroraFrostMeteor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAuroraFrostMeteor::AAuroraFrostMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAuroraFrostMeteor::BeginPlay()
{
	Super::BeginPlay();

    // 0. 높이 고정 이동
    FVector NewLocation = GetActorLocation();
    NewLocation.Z = 1000.f;
    SetActorLocation(NewLocation);

    // 1. MeteorPortal 스폰
    if (MeteorPortal)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            MeteorPortal,
            GetActorTransform(),
            true
        );
    }

    // 2. 0.5초 후 MeteorShower 스폰 예약
    GetWorldTimerManager().SetTimer(
        MeteorTimerHandle,
        this,
        &AAuroraFrostMeteor::SpawnMeteorShower,
        0.5f,
        false
    );
}

// Called every frame
void AAuroraFrostMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAuroraFrostMeteor::SpawnMeteorShower()
{
    if (MeteorShower)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            MeteorShower,
            GetActorTransform(),
            true
        );
    }
}