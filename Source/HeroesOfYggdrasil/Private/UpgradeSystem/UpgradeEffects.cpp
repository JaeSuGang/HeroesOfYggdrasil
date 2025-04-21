// Coded By AssortRock Unreal Engine Class Project


#include "UpgradeSystem/UpgradeEffects.h"

#include "EngineUtils.h"

#include "NPC/Yggdrasil.h"
#include "Attribute/HeroAttributeComponent.h"


void UUpgradeEffect_Stats::ApplyInternal_Implementation(UAttributeComponent* TargetAttribute)
{
	if (UHeroAttributeComponent* CastedTargetAttribute = Cast<UHeroAttributeComponent>(TargetAttribute))
	{
		if (AttackIncrement != 0.0f)
		{
			CastedTargetAttribute->Server_SetAttackPoints(CastedTargetAttribute->AttackPoints + AttackIncrement);
		}

		if (DefenseIncrement != 0.0f)
		{
			CastedTargetAttribute->Server_SetDefensePoints(CastedTargetAttribute->DefensePoints + DefenseIncrement);
		}

		if (HPIncrement != 0.0f)
		{
			CastedTargetAttribute->Server_SetMaxHP(CastedTargetAttribute->MaxHP + HPIncrement);
			CastedTargetAttribute->Server_SetHP(CastedTargetAttribute->HP + HPIncrement);
		}

		if (MoveSpeedIncrement != 0.0f)
		{
			CastedTargetAttribute->Server_SetMaxMoveSpeed(CastedTargetAttribute->MaxMoveSpeed + MoveSpeedIncrement);
		}

		if (AttackSpeedIncrement != 0.0f)
		{
			CastedTargetAttribute->Server_SetAttackSpeedRate(CastedTargetAttribute->AttackSpeedRate + AttackSpeedIncrement);
		}

		if (HPGeneration != 0.0f)
		{
			CastedTargetAttribute->Server_SetHPGeneration(CastedTargetAttribute->HPGeneration + HPGeneration);
		}

		if (CooldownReduction != 0.0f)
		{
			CastedTargetAttribute->CooldownReduction += CooldownReduction;
		}

		if (RespawnTimeReduction != 0.0f)
		{
			CastedTargetAttribute->RespawnTimeReduction += RespawnTimeReduction;
		}

		if (HealInstantly != 0.0f)
		{
			float _NewHp = CastedTargetAttribute->HP + HealInstantly < CastedTargetAttribute->MaxHP ? CastedTargetAttribute->HP + HealInstantly : CastedTargetAttribute->MaxHP;
			CastedTargetAttribute->Server_SetHP(_NewHp);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : UUpgradeEffect_Stats Used Without Setting Target"), __FUNCTION__, __LINE__);
	}
}

void UUpgradeEffect_TeamStats::ApplyInternal_Implementation(UAttributeComponent* TargetAttribute)
{
	for (auto Iter = TargetAttribute->GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		if (APawn* IndividualPawn = Iter->Get()->GetPawn())
		{
			if (UAttributeComponent* IndividualAttribute = Iter->Get()->GetPawn()->GetComponentByClass<UAttributeComponent>())
			{
				Super::ApplyInternal_Implementation(IndividualAttribute);
			}
		}
	}
}

void UUpgradeEffect_World::ApplyInternal_Implementation(UAttributeComponent* TargetAttribute)
{
	if (bHealYggdrasil)
	{
		for (TActorIterator<AYggdrasil> Iter(TargetAttribute->GetWorld()); Iter; ++Iter)
		{
			if (UCharacterAttributeComponent* CAC = (*Iter)->GetComponentByClass<UCharacterAttributeComponent>())
			{
				CAC->Server_SetHP(CAC->MaxHP);
				break;
			}
		}
	}
}
