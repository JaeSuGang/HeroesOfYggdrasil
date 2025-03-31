// Coded By AssortRock Unreal Engine Class Project


#include "Component/SceneComponent/YggCapsuleComponent.h"

#include "Core/YggCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"


void UYggCapsuleComponent::BeginPlay()
{
	OnComponentBeginOverlap.AddDynamic(this, &UYggCapsuleComponent::OverLap);
}


void UYggCapsuleComponent::OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AYggCharacter* DamageCharacter = Cast<AYggCharacter>(OtherActor);
	UCharacterAttributeComponent* DamageCharacterAttributeComponent = DamageCharacter->GetAttributeComponent<UCharacterAttributeComponent>();

	//AYggChara

	///*EnemyAttributeComponent->Server_TakeDamage(10.0f);
	//AIData->PlayData.CurHP -= 10.0f;*/
}

void UYggCapsuleComponent::CollisionOn()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UYggCapsuleComponent::CollisionOff()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
