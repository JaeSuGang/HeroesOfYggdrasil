// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggTickActor.h"

// 캡슐 컴포넌트
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"



// Sets default values
AYggTickActor::AYggTickActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    {
        StatusTickCollision = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("TickCollision"));
        //StatusTickCollision->OnComponentBeginOverlap.AddDynamic(this, &AYggTickActor::OverLapBegin);
    }

    FStatusTickDataRow* Data = StatusTickDataTable->FindRow<FStatusTickDataRow>(FName("Poison"), nullptr);
}

// Called when the game starts or when spawned
void AYggTickActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYggTickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AYggTickActor::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}
