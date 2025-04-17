// TickEffectManager.cpp

#include "Global/TickEffectManager.h"

#include "Global/YggTickActor.h"
#include "Core/YggCharacter.h"
#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"

#include "Component/ActorComponent/TickDamageComponent.h"
#include "Component/ActorComponent/Function/TickUtilityFunctionLibrary.h"
#include "Attribute/CharacterAttributeComponent.h"

#include "Data/YggStructData.h"
#include "Kismet/GameplayStatics.h"

AYggTickActor* UTickEffectManager::SpawnTickActorIfNeeded(
	AYggCharacter* Owner,
	AYggCharacter* Target,
	EStatusEffectType EffectType,
	float TickTime,
	float Scale
)
{
	if (!IsValid(Target)) return nullptr;

	// 이미 부착된 TickActor가 있다면 시간만 갱신
	AYggTickActor* ExistingTickActor = UTickUtilityFunctionLibrary::FindAttachedTickActor(Target);
	if (IsValid(ExistingTickActor))
	{
		FName RowName = ExistingTickActor->StatusRowName;
		FName StatusTag;

		if (Cast<AYggHero>(ExistingTickActor->TickDamageComponent->TargetActor))
			StatusTag = FName(*("Character.DeBuff." + RowName.ToString()));
		else if (Cast<AEnemyCharacter>(ExistingTickActor->TickDamageComponent->TargetActor))
			StatusTag = FName(*("Enemy.DeBuff." + RowName.ToString()));

		UCharacterAttributeComponent* AttrComp = Cast<AYggCharacter>(ExistingTickActor->TickDamageComponent->TargetActor)->GetAttributeComponent();
		if (IsValid(AttrComp) && AttrComp->HasTag(StatusTag))
		{
			if (FStatusTickDataRow* Row = ExistingTickActor->StatusTickDataTable->FindRow<FStatusTickDataRow>(RowName, nullptr))
				ExistingTickActor->StatusTickTime = TickTime;
		}
		return nullptr;
	}

	// 새 TickActor 스폰
	FTransform SpawnTransform(Target->GetActorRotation(), Target->GetActorLocation());

	TSubclassOf<AYggTickActor> TickActorBPClass = LoadClass<AYggTickActor>(
		nullptr,
		TEXT("/Game/Global/BP_YggTickActor.BP_YggTickActor_C")
	);

	if (!TickActorBPClass)
	{
		return nullptr;
	}
	if (!IsValid(Owner) || !Owner->HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("TickEffectManager: Only server should spawn TickActor."));
		return nullptr;
	}

	AYggTickActor* TickActor = Owner->GetWorld()->SpawnActorDeferred<AYggTickActor>(TickActorBPClass, SpawnTransform, Target);


	TickActor->TickDamageComponent->TargetActor = Target;
	TickActor->TickDamageComponent->TickInterval = 0.5f;
	TickActor->TickDamageComponent->DamageAmount = 0.1f;
	TickActor->TickEffectType = EffectType;
	TickActor->StatusTickTime = TickTime;
	TickActor->TickActorScale = Scale;
	TickActor->StatusRowName = UTickUtilityFunctionLibrary::ConvertStatusEffectTypeToName(EffectType);
	FName NewRowName = TickActor->StatusRowName;

	FStatusTickDataRow* DataRow = TickActor->StatusTickDataTable->FindRow<FStatusTickDataRow>(NewRowName, nullptr);

	if (DataRow)
	{
		if (DataRow->NiagaraSystem.IsValid())
		{
			TickActor->NiagaraEffect = DataRow->NiagaraSystem;
		}
		if (DataRow->Particle.IsValid())
		{
			TickActor->ParticleEffect = DataRow->Particle;
		}
	}

	


	UGameplayStatics::FinishSpawningActor(TickActor, SpawnTransform);

	TickActor->SpawnEffect(TickActor->TickDamageComponent->TargetActor);


	if (AYggCharacter* Hero = Cast<AYggHero>(TickActor->TickDamageComponent->TargetActor))
	{
		if (IsValid(Hero))
		{
			TickActor->Tag = FName(*("Character.DeBuff." + TickActor->StatusRowName.ToString()));
			Hero->GetAttributeComponent()->AddTag(TickActor->Tag);
		}
	}
	else if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(TickActor->TickDamageComponent->TargetActor))
	{
		if (IsValid(Enemy))
		{
			TickActor->Tag = FName(*("Enemy.DeBuff." + TickActor->StatusRowName.ToString()));
			Enemy->GetAttributeComponent()->AddTag(TickActor->Tag);
		}
	}



	return TickActor;
}
