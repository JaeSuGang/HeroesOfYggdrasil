// Coded By AssortRock Unreal Engine Class Project


#include "NPC/Yggdrasil.h"
#include <Components/SceneComponent.h>
#include "Attribute/CharacterAttributeComponent.h"

AYggdrasil::AYggdrasil()
{
	CharacterAttributeComponent = CreateDefaultSubobject<UCharacterAttributeComponent>("Attribute");
	CharacterAttributeComponent->MaxHP = 100.f;
	CharacterAttributeComponent->HP = 100.f;

}
