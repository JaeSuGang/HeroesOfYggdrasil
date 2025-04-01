// Coded By AssortRock Unreal Engine Class Project


#include "Component/SceneComponent/YggCapsuleComponent.h"

#include "Core/YggCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"


void UYggCapsuleComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UYggCapsuleComponent::OverLapBegin);
	CollisionOff();
}


void UYggCapsuleComponent::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
	UCharacterAttributeComponent* DamageCharacterAttributeComponent = DamageCharacter->GetAttributeComponent();
	if (!IsValid(DamageCharacterAttributeComponent))
	{
		return;
	}
	DamageCharacterAttributeComponent->Server_TakeDamage(10.0f);
	FString CurHP = FString::Printf(TEXT("HP : %f"), DamageCharacterAttributeComponent->GetHP());
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, CurHP);
}

void UYggCapsuleComponent::CollisionOn()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UYggCapsuleComponent::CollisionOff()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
