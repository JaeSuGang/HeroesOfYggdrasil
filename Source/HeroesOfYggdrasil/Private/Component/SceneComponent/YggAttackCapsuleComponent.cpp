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
	if (!OwnerCharacter->HasAuthority()) { return; }
	if (DamageType == EDamageType::Tick)
	{
		CurTime += DeltaTime;
		if (CurTime > DelayTime)
		{
			for (auto& OverlappedActor : OverlappedActors)
			{
				if (IsValid(OverlappedActor))
				{
					if (nullptr != Cast<AYggCharacter>(OverlappedActor))
					{
						UCharacterAttributeComponent* DamageCharacterAttributeComponent = Cast<AYggCharacter>(OverlappedActor)->GetAttributeComponent();
						UCharacterAttributeComponent* CharacterAttributeComponent = OwnerCharacter->GetAttributeComponent();
						if (!DamageCharacterAttributeComponent) { continue; }
						if (!CharacterAttributeComponent) { continue; }
						
						float Damage = DamageLogic(CharacterAttributeComponent, DamageCharacterAttributeComponent);
						

						DamageCharacterAttributeComponent->Server_TakeDamage(Damage);
						// 지워도됨
						FString DamageStr = FString::Printf(TEXT("TickDamage : %f"), Damage);
						GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Green, DamageStr);
					}
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
	if (!DamageCharacter) return;
	UCharacterAttributeComponent* DamageCharacterAttributeComponent = DamageCharacter->GetAttributeComponent();
	UCharacterAttributeComponent* AttackCharacterAttributeComponent = OwnerCharacter->GetAttributeComponent();

	if (!AttackCharacterAttributeComponent|| !DamageCharacterAttributeComponent) { return; }

	float Damage = DamageLogic(AttackCharacterAttributeComponent, DamageCharacterAttributeComponent);



	DamageCharacterAttributeComponent->Server_TakeDamage(Damage);
	FString DamageStr = FString::Printf(TEXT("Damage : %f"), Damage);
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Green, DamageStr);

	PlusLogic.Broadcast();
}

void UYggAttackCapsuleComponent::CollisionOn()
{
	Super::CollisionOn();
	OverlappedActors.Reset();
	SetComponentTickEnabled(true);
	if (OwnerCharacter == nullptr)
	{
		return;
	}

	if (CharacterType == ECharacterType::Hero)
	{
		UHeroAttributeComponent* HeroAttributeComponent = Cast<UHeroAttributeComponent>(OwnerCharacter->GetAttributeComponent());
		if (!HeroAttributeComponent) return;
		
		switch (AttackType)
		{
		case EAttackType::Normal:
			Coefficient = 1.0f;
			break;
		case EAttackType::SkillQ:
			Coefficient = HeroAttributeComponent->SkillQInfo.SkillCoefficient;
			break;
		case EAttackType::SkillE:
			Coefficient = HeroAttributeComponent->SkillEInfo.SkillCoefficient;
			break;
		case EAttackType::SkillR:
			Coefficient = HeroAttributeComponent->SkillRInfo.SkillCoefficient;
			break;
		}
	}
}

float UYggAttackCapsuleComponent::DamageLogic(UCharacterAttributeComponent* Attack, UCharacterAttributeComponent* Hit)
{
	UCharacterAttributeComponent* AttackAttributeComponent = Attack;
	UCharacterAttributeComponent* HitAttributeComponent = Hit;
	float Damage;
	// 공격력 계산
	Damage = AttackAttributeComponent->AttackPoints* Coefficient;
	// 방어력 계산
	Damage = Damage * (100 / (100 + HitAttributeComponent->DefensePoints));
	// 크리티컬 확률 계산
	if (FMath::FRand() <= AttackAttributeComponent->CriticalChance)
	{
		Damage = Damage * (1 + AttackAttributeComponent->CriticalDamageRate);
	}
	return Damage;
}

void UYggAttackCapsuleComponent::OverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappedActors.Remove(OtherActor);
}
