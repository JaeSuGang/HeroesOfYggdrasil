// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/HeroAttributeComponent.h"
#include "Engine/DataTable.h"
#include "Net/UnrealNetwork.h"

#include "Data/YggStructData.h"

void UHeroAttributeComponent::BeginPlay()
{
    Super::BeginPlay();   
    
}

void UHeroAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHeroAttributeComponent, HPRegen);
	DOREPLIFETIME(UHeroAttributeComponent, GroundSpeedRate);
	DOREPLIFETIME(UHeroAttributeComponent, JumpRate);
	DOREPLIFETIME(UHeroAttributeComponent, AttackSpeedRate);
	DOREPLIFETIME(UHeroAttributeComponent, CriticalChance);
	DOREPLIFETIME(UHeroAttributeComponent, CriticalDamageRate);
}

void UHeroAttributeComponent::ServerSetBaseData_Implementation(const FName& Name)
{
	if (BaseData)
	{
		FHeroBaseStatusInfoRow* Data = BaseData->FindRow<FHeroBaseStatusInfoRow>(Name, nullptr);
		if (Data)
		{
			MaxHP = Data->MaxHP;
			HP = MaxHP;
			HPRegen = Data->HPRegen;
			GroundSpeedRate = Data->GroundSpeedRate;
			JumpRate = Data->JumpRate;
			AttackSpeedRate = Data->AttackSpeedRate;
			CriticalChance = Data->CriticalChance;
			CriticalDamageRate = Data->CriticalDamageRate;
		}
	}
}

bool UHeroAttributeComponent::IsAttackCheck()
{
	return HasTagExact(TEXT("Character.State.NotAttackable"));
}
