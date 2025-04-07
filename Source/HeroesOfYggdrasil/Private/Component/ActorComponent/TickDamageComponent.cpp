// Coded By AssortRock Unreal Engine Class Project


#include "Component/ActorComponent/TickDamageComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Core/YggCharacter.h"
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

	if (!IsValid(TargetActor)) return;

	// 이 태그를 이미 가졌다면
	if (TargetActor->GetAttributeComponent()->HasTagExact(TEXT("Player.Status.Poison")))
	{
		return;
	}

	ElapsedTime += DeltaTime;

	if (ElapsedTime >= TickInterval)
	{
		ApplyDamage();
		ElapsedTime = 0.0f;
	}
}


void UTickDamageComponent::ApplyDamage()
{
	if (IsValid(TargetActor))
	{
		TargetActor->GetAttributeComponent()->HP -= DamageAmount;
		UE_LOG(LogTemp, Log, TEXT("TickDamage: %.1f applied to %s"), DamageAmount, *TargetActor->GetName());
	}
}