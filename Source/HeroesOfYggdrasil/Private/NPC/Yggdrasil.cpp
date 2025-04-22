// Coded By AssortRock Unreal Engine Class Project


#include "NPC/Yggdrasil.h"
#include <Components/SceneComponent.h>
#include "Attribute/CharacterAttributeComponent.h"
// #include <Kismet/GameplayStatics.h>
#include "StageSystem/StageSystem.h"

AYggdrasil::AYggdrasil()
{
	CharacterAttributeComponent = CreateDefaultSubobject<UCharacterAttributeComponent>("Attribute");
	CharacterAttributeComponent->MaxHP = 500.f;
	CharacterAttributeComponent->HP = 500.f;


}

void AYggdrasil::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributeComponent->ClientDelegate_OnTakeDamage.AddDynamic(this, &AYggdrasil::CheckHP);
}

void AYggdrasil::CheckHP(float _NULL)
{
	if (bIsLive == false)
	{
		return;
	}

	if (nullptr != GetWorld()->GetAuthGameMode())
	{
		if (CharacterAttributeComponent->HP <= 0.f)
		{
			bIsLive = false;
			UStageSystem::Get(GetWorld())->DefeatInternal();
		}
	}
	
}