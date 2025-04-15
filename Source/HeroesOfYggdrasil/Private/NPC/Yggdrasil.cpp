// Coded By AssortRock Unreal Engine Class Project


#include "NPC/Yggdrasil.h"
#include <Components/SceneComponent.h>
#include "Attribute/CharacterAttributeComponent.h"
#include "StageSystem/StageSystem.h"

AYggdrasil::AYggdrasil()
{
	CharacterAttributeComponent = CreateDefaultSubobject<UCharacterAttributeComponent>("Attribute");
	CharacterAttributeComponent->MaxHP = 5.f;
	CharacterAttributeComponent->HP = 5.f;


}

void AYggdrasil::Tick(float DeltaTime)
{
	if (nullptr != GetWorld()->GetAuthGameMode())
	{
		if (CharacterAttributeComponent->HP <= 0.f)
		{
			UStageSystem::Get(GetWorld())->DefeatInternal();
		}
	}
}
