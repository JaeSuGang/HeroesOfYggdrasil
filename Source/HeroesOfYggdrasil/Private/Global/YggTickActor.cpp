// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggTickActor.h"

// 캡슐 컴포넌트
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Engine/DataTable.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"


// Sets default values
AYggTickActor::AYggTickActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));

    {
        StatusTickCollision = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("TickCollision"));
        StatusTickCollision->SetupAttachment(DefualtSceneRoot);
        
        //StatusTickCollision->OnComponentBeginOverlap.AddDynamic(this, &AYggTickActor::OverLapBegin);
    }


}

// Called when the game starts or when spawned
void AYggTickActor::BeginPlay()
{
	Super::BeginPlay();

    StatusTickCollision->CollisionOn();

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

// Called every frame
void AYggTickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AYggTickActor::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    int a = 0;
}
