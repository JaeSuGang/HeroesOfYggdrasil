// Coded By AssortRock Unreal Engine Class Project


#include "Component/SceneComponent/YggCapsuleComponent.h"





void UYggCapsuleComponent::BeginPlay()
{
	Super::BeginPlay();
	if (OwnerCharacter == nullptr)
	{
		//UE_LOG(LogTemp, Fatal, TEXT("OwnerCharacter is nullptr"));
	}
}

void UYggCapsuleComponent::CollisionOn()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UYggCapsuleComponent::CollisionOff()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetComponentTickEnabled(false);
}
