// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggTickActor.h"

// Sets default values
AYggTickActor::AYggTickActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

