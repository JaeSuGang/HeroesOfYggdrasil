// Coded By AssortRock Unreal Engine Class Project


#include "Upgrade/UpgradeEffects.h"

#include "Attribute/HeroAttributeComponent.h"


void UUpgradeEffect_Stats::Apply_Implementation(UHeroAttributeComponent* TargetAttribute)
{
	if (TargetAttribute)
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
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : UUpgradeEffect_Stats Used Without Setting Target"), __FUNCTION__, __LINE__);
	}
}

void UUpgradeEffect_TeamStats::Apply_Implementation()
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
