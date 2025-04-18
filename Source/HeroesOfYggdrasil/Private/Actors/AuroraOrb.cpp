// Coded By AssortRock Unreal Engine Class Project


#include "Actors/AuroraOrb.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"
#include "Enemy/EnemyCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AAuroraOrb::AAuroraOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    OrbCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OrbCapsule"));
    SetRootComponent(OrbCapsule);
    OrbCapsule->InitCapsuleSize(20.f, 20.f);
    OrbCapsule->AddRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
    OrbCapsule->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
    OrbCapsule->SetHiddenInGame(true);
    OrbCapsule->SetVisibility(true);

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(OrbCapsule);
    MeshComp->SetRelativeLocation(FVector::ZeroVector);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    OrbCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAuroraOrb::OnOrbOverlapBegin);
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

    if (PSTrail)
    {
        UGameplayStatics::SpawnEmitterAttached(
            PSTrail,
            OrbCapsule,
            NAME_None,
            FVector::ZeroVector,
            FRotator::ZeroRotator,
            EAttachLocation::KeepRelativeOffset,
            true
        );
    }
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

void AAuroraOrb::OnOrbOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor);
        if (!IsValid(Enemy)) return;

        Enemy->GetAttributeComponent()->Server_TakeDamage(AttPower);

        if (PSImpact)
        {
            UGameplayStatics::SpawnEmitterAtLocation(
                GetWorld(),
                PSImpact,
                GetActorLocation(),
                GetActorRotation()
            );
        }

        this->Destroy();
    }
}
