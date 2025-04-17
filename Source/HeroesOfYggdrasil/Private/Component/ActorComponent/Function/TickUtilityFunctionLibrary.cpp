// Coded By AssortRock Unreal Engine Class Project


#include "Component/ActorComponent/Function/TickUtilityFunctionLibrary.h"
#include "Global/YggTickActor.h"
#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"


AYggTickActor* UTickUtilityFunctionLibrary::FindAttachedTickActor(AYggCharacter* HeroTarget)
{
	if (!IsValid(HeroTarget)) return nullptr;

	TArray<AActor*> AttachedActors;
	HeroTarget->GetAttachedActors(AttachedActors);

	for (AActor* Actor : AttachedActors)
	{
		if (AYggTickActor* TickActor = Cast<AYggTickActor>(Actor))
		{
			return TickActor;
		}
	}

	return nullptr;
}

EStatusEffectType UTickUtilityFunctionLibrary::FindStatusEffectType(AEnemyCharacter* Enemy)
{
	if (!IsValid(Enemy)) return EStatusEffectType::MAX;

	const FString& Key = Enemy->GetDataKey();

	if (Key == TEXT("Minion_Witch_0")) return EStatusEffectType::Poison;
	if (Key == TEXT("Minion_Witch_1")) return EStatusEffectType::Slow;
	if (Key == TEXT("Minion_Witch_2")) return EStatusEffectType::Stunned;
	if (Key == TEXT("Minion_Witch_3")) return EStatusEffectType::Burn;
	if (Key == TEXT("Dragon"))		   return EStatusEffectType::Burn;

	return EStatusEffectType::MAX;
}

FName UTickUtilityFunctionLibrary::ConvertStatusEffectTypeToName(EStatusEffectType Type)
{
	switch (Type)
	{
	case EStatusEffectType::Poison:	return FName("Poison");
	case EStatusEffectType::Burn:	return FName("Burn");
	case EStatusEffectType::Slow:	return FName("Slow");
	case EStatusEffectType::Stunned: return FName("Stunned");
	default: return NAME_None;
	}
}