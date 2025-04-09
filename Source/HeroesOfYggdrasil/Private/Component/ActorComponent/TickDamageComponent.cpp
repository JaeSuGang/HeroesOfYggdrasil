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
			if (HeroTarget->GetAttributeComponent()->HasTag(TEXT("Character.DeBuff")))
			{
				HeroTarget->GetAttributeComponent()->Server_TakeDamage(DamageAmount);
				return;
			}
			else if (HeroTarget->GetAttributeComponent()->HasTag(TEXT("Character.Buff")))
			{
				HeroTarget->GetAttributeComponent()->Server_TakeDamage(-DamageAmount);
				return;
			}
		}
	}
	else if (IsValid(EnemyTarget))
	{
		if (EnemyTarget->GetAttributeComponent()->HasTag(TEXT("Enemy.DeBuff")))
		{
			EnemyTarget->GetAttributeComponent()->Server_TakeDamage(DamageAmount);
			return;
		}
		else if (EnemyTarget->GetAttributeComponent()->HasTag(TEXT("Enemy.Buff")))
		{
			EnemyTarget->GetAttributeComponent()->Server_TakeDamage(-DamageAmount);
			return;
		}
	}

}