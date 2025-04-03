// Coded By AssortRock Unreal Engine Class Project


#include "Component/SceneComponent/YggCapsuleComponent.h"





void UYggCapsuleComponent::CollisionOn()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UYggCapsuleComponent::CollisionOff()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
