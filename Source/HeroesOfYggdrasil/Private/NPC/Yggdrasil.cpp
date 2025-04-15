// Coded By AssortRock Unreal Engine Class Project


#include "NPC/Yggdrasil.h"
#include <Components/SceneComponent.h>
#include "Attribute/CharacterAttributeComponent.h"

AYggdrasil::AYggdrasil()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	CharacterAttributeComponent = CreateDefaultSubobject<UCharacterAttributeComponent>("Attribute");
	CharacterAttributeComponent->MaxHP = 100.f;
	CharacterAttributeComponent->HP = 100.f;
}
