// Coded By AssortRock Unreal Engine Class Project


#include "NPC/Yggdrasil.h"
#include <Components/SceneComponent.h>
#include "Attribute/CharacterAttributeComponent.h"
// #include <Kismet/GameplayStatics.h>
#include "StageSystem/StageSystem.h"

AYggdrasil::AYggdrasil()
{
	CharacterAttributeComponent = CreateDefaultSubobject<UCharacterAttributeComponent>("Attribute");
	CharacterAttributeComponent->MaxHP = 1.f;
	CharacterAttributeComponent->HP = 1.f;


}

void AYggdrasil::BeginPlay()
{
	Super::BeginPlay();

	CharacterAttributeComponent->ClientDelegate_OnTakeDamage.AddDynamic(this, &AYggdrasil::CheckHP);
}

//void AYggdrasil::Tick(float DeltaTime)
//{
//	if (nullptr != GetWorld()->GetAuthGameMode())
//	{
//		if (CharacterAttributeComponent->HP <= 0.f)
//		{
//			UStageSystem::Get(GetWorld())->DefeatInternal();
//		}
//	}
//}

void AYggdrasil::CheckHP(float _NULL)
{
	if (nullptr != GetWorld()->GetAuthGameMode())
	{
		if (CharacterAttributeComponent->HP <= 0.f)
		{
			UStageSystem::Get(GetWorld())->DefeatInternal();
		}
	}

	// UGameplayStatics::getactor()


}