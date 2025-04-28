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
	CatalystCapsule->SetCollisionResponseToAllChannels(ECR_Ignore);

	CatalystCapsule->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block); // 땅
	CatalystCapsule->SetCollisionResponseToChannel(ECC_GameTraceChannel5, ECR_Block); // 벽
	CatalystCapsule->SetCollisionResponseToChannel(ECC_GameTraceChannel6, ECR_Block); // 나무

	CatalystCapsule->OnComponentHit.AddDynamic(this, &AAuroraFrostCatalyst::OnCatalystHit);
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

void AAuroraFrostCatalyst::OnCatalystHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString("zfzfzf"));
		
	// 충돌 지점에 메테오 스폰
	if (MeteorClass)
	{
		FVector SpawnLoc = Hit.ImpactPoint;
		FRotator SpawnRot = FRotator::ZeroRotator;
		
		AAuroraFrostMeteor* Meteor = GetWorld()->SpawnActor<AAuroraFrostMeteor>(MeteorClass, SpawnLoc, SpawnRot);
		if (!Meteor) return;
	}

	Destroy();	
}