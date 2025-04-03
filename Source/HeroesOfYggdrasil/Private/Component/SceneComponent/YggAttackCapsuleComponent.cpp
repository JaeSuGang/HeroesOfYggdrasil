// Coded By AssortRock Unreal Engine Class Project


#include "Component/SceneComponent/YggAttackCapsuleComponent.h"


#include "Core/YggCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Data/YggStructData.h"


void UYggAttackCapsuleComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &UYggAttackCapsuleComponent::OverLapBegin);
	CollisionOff();
}

void UYggAttackCapsuleComponent::CollisionOn()
{
	Super::CollisionOn();

}



void UYggAttackCapsuleComponent::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
	if (!DamageCharacterAttributeComponent)
	{
		return;
	}
	UCharacterAttributeComponent* AttackCharacterAttributeComponent = Cast<AYggCharacter>(GetOwner())->GetAttributeComponent();
	if (!AttackCharacterAttributeComponent)
	{
		return;
	}


	float AttackPower = AttackCharacterAttributeComponent->GetAttackPoints();
	float Coefficient = 1.0f;
	switch (AttackType) 
	{
	case EAttackType::SkillQ:
		Coefficient = Cast<UHeroAttributeComponent>(AttackCharacterAttributeComponent)->SkillQInfo.SkillCoefficient;
		break;
	case EAttackType::SkillE:
		Coefficient = Cast<UHeroAttributeComponent>(AttackCharacterAttributeComponent)->SkillEInfo.SkillCoefficient;
		break;
	case EAttackType::SkillR:
		Coefficient = Cast<UHeroAttributeComponent>(AttackCharacterAttributeComponent)->SkillRInfo.SkillCoefficient;
		break;
	}
	DamageCharacterAttributeComponent->Server_TakeDamage(AttackPower * Coefficient);
	
	FString Damage = FString::Printf(TEXT("Damage : %f"), AttackPower * Coefficient);

	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, Damage);
	FString CurHP = FString::Printf(TEXT("HP : %f"), DamageCharacterAttributeComponent->GetHP());

	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, CurHP);
}