// Coded By AssortRock Unreal Engine Class Project


#include "UpgradeSystem/UpgradeEffects.h"

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
		}

		if (MoveSpeedIncrement != 0.0f)
		{
			CastedTargetAttribute->Server_SetMaxMoveSpeed(CastedTargetAttribute->MaxMoveSpeed + MoveSpeedIncrement);
		}

		if (AttackSpeedIncrement != 0.0f)
		{
			CastedTargetAttribute->Server_SetAttackSpeedRate(CastedTargetAttribute->AttackSpeedRate + AttackSpeedIncrement);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : UUpgradeEffect_Stats Used Without Setting Target"), __FUNCTION__, __LINE__);
	}
}

void UUpgradeEffect_TeamStats::ApplyInternal_Implementation(UAttributeComponent* TargetAttribute)
{
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		if (APlayerController* PC = Cast<APlayerController>(Iter->Get()))
		{
			if (PC->GetPawn())
			{
				if (UHeroAttributeComponent* TargetAttribute = Cast<UHeroAttributeComponent>(PC->GetPawn()->GetComponentByClass<UHeroAttributeComponent>()))
				{
					if (AttackIncrement != 0.0f)
					{
						TargetAttribute->Server_SetAttackPoints(TargetAttribute->AttackPoints + AttackIncrement);
					}

					if (DefenseIncrement != 0.0f)
					{
						TargetAttribute->Server_SetDefensePoints(TargetAttribute->DefensePoints + DefenseIncrement);
					}

					if (HPIncrement != 0.0f)
					{
						TargetAttribute->Server_SetMaxHP(TargetAttribute->MaxHP + HPIncrement);
					}

					if (MoveSpeedIncrement != 0.0f)
					{
						TargetAttribute->Server_SetMaxMoveSpeed(TargetAttribute->MaxMoveSpeed + MoveSpeedIncrement);
					}

					if (AttackSpeedIncrement != 0.0f)
					{
						TargetAttribute->Server_SetAttackSpeedRate(TargetAttribute->AttackSpeedRate + AttackSpeedIncrement);
					}
				}

			}
		}
	}
}
