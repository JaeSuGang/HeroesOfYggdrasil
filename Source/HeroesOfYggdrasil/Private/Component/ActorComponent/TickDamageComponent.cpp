// Coded By AssortRock Unreal Engine Class Project


#include "Component/ActorComponent/TickDamageComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Core/YggCharacter.h"

#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"

#include "Attribute/CharacterAttributeComponent.h"




UTickDamageComponent::UTickDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTickDamageComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTickDamageComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UTickDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ElapsedTime += DeltaTime;

	if (ElapsedTime >= TickInterval)
	{
		ApplyDamage();
		ElapsedTime = 0.0f;
	}
}


void UTickDamageComponent::ApplyDamage()
{
	AYggCharacter* HeroTarget = Cast<AYggHero>(TargetActor);

	AEnemyCharacter* EnemyTarget = Cast<AEnemyCharacter>(TargetActor);

	
	if (IsValid(HeroTarget))
	{
		if (HeroTarget->HasAuthority())
		{
			// 추후 태그체크로 데미지 함수 이동
			if (true == HeroTarget->GetAttributeComponent()->HasTag(TEXT("Character.DeBuff.Poision")))
			{
				HeroTarget->GetAttributeComponent()->Server_TakeDamage(DamageAmount);
				return;
			}
		}
	}
	else if (IsValid(EnemyTarget))
	{
		/*if (EnemyTarget->GetAttributeComponent()->HasTag(TEXT("Character.State")))
		{
			EnemyTarget->GetAttributeComponent()->Server_TakeDamage(DamageAmount);
			UE_LOG(LogTemp, Log, TEXT("TickDamage: %.1f applied to %s"), DamageAmount, *EnemyTarget->GetName());
			return;
		}*/
	}
	else
	{
		return;
	}
}