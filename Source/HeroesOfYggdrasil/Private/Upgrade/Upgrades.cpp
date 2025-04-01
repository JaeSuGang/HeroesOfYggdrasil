// Coded By AssortRock Unreal Engine Class Project


#include "Upgrade/Upgrades.h"

#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"

/*
* 현재 Upgrade 클래스의 종속성
* - AYGGHero
* - UHeroAttributeComponent
*/

void UHeroUpgradeBase::Apply_Implementation(APlayerController* PC, float fValueToApply)
{

}

void UHeroUpgrade_Attack::Apply_Implementation(APlayerController* PC, float fValueToApply)
{
	Super::Apply_Implementation(PC, fValueToApply);

	fValueToApply = 5.0f;

	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float fUpgradedValue = HAC->GetAttackPoints() + fValueToApply;
			HAC->Server_SetAttackPoints(fUpgradedValue);
		}
	}
}

void UHeroUpgrade_Defense::Apply_Implementation(APlayerController* PC, float fValueToApply)
{
	Super::Apply_Implementation(PC, fValueToApply);

	fValueToApply = 10.0f;

	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float fUpgradedValue = HAC->GetDefensePoints() + fValueToApply;
			HAC->Server_SetDefensePoints(fUpgradedValue);
		}
	}
}

void UHeroUpgrade_HP::Apply_Implementation(APlayerController* PC, float fValueToApply)
{
	Super::Apply_Implementation(PC, fValueToApply);

	fValueToApply = 10.0f;

	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float fUpgradedValue = HAC->GetMaxHP() + fValueToApply;
			HAC->Server_SetMaxHP(fUpgradedValue);
		}
	}
}

void UHeroUpgrade_MoveSpeed::Apply_Implementation(APlayerController* PC, float fValueToApply)
{
	Super::Apply_Implementation(PC, fValueToApply);

	fValueToApply = 20.0f;

	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float fUpgradedValue = HAC->GetMaxMoveSpeed() + fValueToApply;
			HAC->Server_SetMaxMoveSpeed(fUpgradedValue);
		}
	}
}

void UHeroUpgrade_AttackSpeed::Apply_Implementation(APlayerController* PC, float fValueToApply)
{
	Super::Apply_Implementation(PC, fValueToApply);

	fValueToApply = 0.1f;

	if (AYggHero* Hero = Cast<AYggHero>(PC->GetPawn()))
	{
		if (UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent())
		{
			float fUpgradedValue = HAC->GetAttackSpeedRate() + fValueToApply;
			HAC->Server_SetAttackSpeedRate(fUpgradedValue);
		}
	}
}