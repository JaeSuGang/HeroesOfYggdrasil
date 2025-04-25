// Coded By AssortRock Unreal Engine Class Project


#include "Actors/AuroraFrostCatalyst.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Actors/AuroraFrostMeteor.h"

// Sets default values
AAuroraFrostCatalyst::AAuroraFrostCatalyst()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CatalystCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OrbCapsule"));
	SetRootComponent(CatalystCapsule);
	CatalystCapsule->InitCapsuleSize(50.f, 50.f);
	CatalystCapsule->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	MeshComp1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp1"));
	MeshComp1->SetupAttachment(CatalystCapsule);
	MeshComp1->SetRelativeLocation(FVector::ZeroVector);
	MeshComp1->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp2"));
	MeshComp2->SetupAttachment(CatalystCapsule);
	MeshComp2->SetRelativeLocation(FVector::ZeroVector);
	MeshComp2->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = false;
	ProjectileMovement->ProjectileGravityScale = 1.f;
	ProjectileMovement->InitialSpeed = 0.f;
	ProjectileMovement->MaxSpeed = 2000.f;

	CatalystCapsule->SetCollisionProfileName(TEXT("Custom"));
	CatalystCapsule->SetCollisionObjectType(ECC_WorldDynamic);
	CatalystCapsule->SetCollisionResponseToAllChannels(ECR_Overlap);
	CatalystCapsule->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap); // 땅과 Overlap
	CatalystCapsule->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Overlap); // 벽과 Overlap

	CatalystCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAuroraFrostCatalyst::OnCatalystOverlapBegin);
}

// Called when the game starts or when spawned
void AAuroraFrostCatalyst::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAuroraFrostCatalyst::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAuroraFrostCatalyst::OnCatalystOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp && (
		OtherComp->GetCollisionObjectType() == ECC_WorldStatic ||
		OtherComp->GetCollisionObjectType() == ECC_GameTraceChannel5))
	{
		UWorld* World = GetWorld();
		if (World && MeteorClass)
		{
			FVector SpawnLoc = SweepResult.ImpactPoint;
			FRotator SpawnRot = GetActorRotation();

			World->SpawnActor<AAuroraFrostMeteor>(
				MeteorClass,
				SpawnLoc,
				SpawnRot
			);
		}

		Destroy();
	}
}
