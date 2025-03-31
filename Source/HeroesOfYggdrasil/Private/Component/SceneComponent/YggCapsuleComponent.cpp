// Coded By AssortRock Unreal Engine Class Project


#include "Component/SceneComponent/YggCapsuleComponent.h"

#include "Core/YggCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"


void UYggCapsuleComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UYggCapsuleComponent::OverLap);
}


void UYggCapsuleComponent::OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetOwner() || !GetOwner()->HasAuthority())
	{
		return;
	}
	AYggCharacter* DamageCharacter = Cast<AYggCharacter>(OtherActor);
	if (!IsValid(DamageCharacter))
	{
		return;
	}
	UCharacterAttributeComponent* CharacterAttributeComponent = DamageCharacter->GetAttributeComponent();
	if (!IsValid(CharacterAttributeComponent))
	{
		return;
	}
	CharacterAttributeComponent->Server_TakeDamage(10.0f);
	FString CurHP = FString::Printf(TEXT("HP : %f"), CharacterAttributeComponent->GetHP());
}

void UYggCapsuleComponent::CollisionOn()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UYggCapsuleComponent::CollisionOff()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
