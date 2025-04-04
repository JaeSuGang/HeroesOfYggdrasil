// Coded By AssortRock Unreal Engine Class Project


#include "Component/SceneComponent/YggAttackCapsuleComponent.h"


#include "Core/YggCharacter.h"
#
#include "Attribute/CharacterAttributeComponent.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Data/YggStructData.h"


UYggAttackCapsuleComponent::UYggAttackCapsuleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UYggAttackCapsuleComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OnComponentBeginOverlap.AddDynamic(this, &UYggAttackCapsuleComponent::OverLapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UYggAttackCapsuleComponent::OverLapEnd);
	CollisionOff();
}

void UYggAttackCapsuleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!IsValid(OwnerCharacter)) { return; }
	if(!OwnerCharacter->HasAuthority()) { return; }
	if (DamageType == EDamageType::Tick)
	{
		CurTime += DeltaTime;
		if (CurTime > DelayTime)
		{
			for (auto& OverlappedActor : OverlappedActors)
			{
				if (IsValid(OverlappedActor))
				{
					UCharacterAttributeComponent* DamageCharacterAttributeComponent = Cast<AYggCharacter>(OverlappedActor)->GetAttributeComponent();
					UCharacterAttributeComponent* CharacterAttributeComponent = OwnerCharacter->GetAttributeComponent();
					if (!DamageCharacterAttributeComponent) { continue; }
					if (!CharacterAttributeComponent) { continue; }
					DamageCharacterAttributeComponent->Server_TakeDamage(CharacterAttributeComponent->AttackPoints * Coefficient);


					// 지워도됨
					FString Damage = FString::Printf(TEXT("TickDamage : %f"), CharacterAttributeComponent->AttackPoints * Coefficient);
					GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, Damage);
				}
			}
			CurTime = 0.0f;
		}
	}
}


void UYggAttackCapsuleComponent::OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OwnerCharacter || !OwnerCharacter->HasAuthority()) { return; }
	if (!IsValid(OtherActor)) { return; }
	OverlappedActors.Add(OtherActor);

	AYggCharacter* DamageCharacter = Cast<AYggCharacter>(OtherActor);
	UCharacterAttributeComponent* DamageCharacterAttributeComponent = DamageCharacter->GetAttributeComponent();
	if (!DamageCharacterAttributeComponent) { return; }
	UCharacterAttributeComponent* AttackCharacterAttributeComponent = OwnerCharacter->GetAttributeComponent();
	if (!AttackCharacterAttributeComponent) { return; }
	DamageCharacterAttributeComponent->Server_TakeDamage(AttackCharacterAttributeComponent->GetAttackPoints() * Coefficient);

	// 지워도됨
	FString Damage = FString::Printf(TEXT("Damage : %f"), AttackCharacterAttributeComponent->GetAttackPoints() * Coefficient);
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, Damage);
	FString CurHP = FString::Printf(TEXT("HP : %f"), DamageCharacterAttributeComponent->GetHP());
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, CurHP);
}

void UYggAttackCapsuleComponent::CollisionOn()
{
	Super::CollisionOn();
	OverlappedActors.Reset();
	SetComponentTickEnabled(true);
}

void UYggAttackCapsuleComponent::OverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappedActors.Remove(OtherActor);
}
