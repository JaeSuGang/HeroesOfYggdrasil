// Coded By AssortRock Unreal Engine Class Project


#include "Component/ActorComponent/Function/TickUtilityFunctionLibrary.h"
#include "Global/YggTickActor.h"
#include "Player/YggHero.h"


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
