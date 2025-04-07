// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggTickActor.h"

// 캡슐 컴포넌트
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Engine/DataTable.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Component/ActorComponent/TickDamageComponent.h"

#include "Core/YggCharacter.h"

#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AYggTickActor::AYggTickActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
    TickDamageComponent = CreateDefaultSubobject<UTickDamageComponent>(TEXT("TickDamageComp"));
}

// Called when the game starts or when spawned
void AYggTickActor::BeginPlay()
{
	Super::BeginPlay();


      if (IsValid(StatusTickDataTable))
    {
        FStatusTickDataRow* Row = StatusTickDataTable->FindRow<FStatusTickDataRow>(FName("Poison"), nullptr);

        if (TickNiagaraSystem != nullptr)
        {
            TickNiagaraSystem = Row->NiagaraSystem;
        }

        if (TickParticle != nullptr)
        {
            TickParticle = Row->Particle;
        }

        StatusTickTime = Row->TickTime;
    }

}

void AYggTickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    StatusTickTime -= DeltaTime;

    if (StatusTickTime < 0.0f)
    {
        Destroy();
    }
}

void AYggTickActor::SetTickDamage(AYggCharacter* _Target, float _Interval, float DamageAmount)
{
    TickDamageComponent->TargetActor = _Target;
    TickDamageComponent->TickInterval = _Interval;
    TickDamageComponent->DamageAmount = DamageAmount;
}
