// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/AttributeComponent.h"
#include "HeroAttributeComponent.generated.h"

/**
 *	김성훈
 */
UCLASS()
class HEROESOFYGGDRASIL_API UHeroAttributeComponent : public UAttributeComponent
{
	GENERATED_BODY()

protected:
	float Hp;

	// 나중에 구조체로 묶어
	bool bIsContinueSkillQ;
	float CoolTimeSkillQ;
	float ContinueTimeSkillQ;

	bool bIsContinueSkillE;
	float CoolTimeSkillE;
	float ContinueTimeSkillE;

	bool bIsContinueSkillR;
	float CoolTimeSkillR;
	float ContinueTimeSkillR;

};
