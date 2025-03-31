// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/HeroAttributeComponent.h"
#include "Engine/DataTable.h"
#include "Net/UnrealNetwork.h"

#include "Data/YggStructData.h"

UHeroAttributeComponent::UHeroAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeroAttributeComponent::BeginPlay()
{
    Super::BeginPlay();   
    
}

void UHeroAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (SkillQCurCoolTime > 0.0f)
		SkillQCurCoolTime -= DeltaTime;
	if (SkillECurCoolTime > 0.0f)
		SkillECurCoolTime -= DeltaTime;
	if (SkillRCurCoolTime > 0.0f)
		SkillRCurCoolTime -= DeltaTime;

	if (CurRollCount < MaxRollCount)
	{
		RollCurCoolTime += DeltaTime;

		if (RollCurCoolTime >= RollMaxCoolTime)
		{
			RollCurCoolTime = 0.0f;
			CurRollCount++;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,
		FString::Printf(TEXT("CurRollCount: %d"), CurRollCount));
}

void UHeroAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHeroAttributeComponent, HPRegen);
	DOREPLIFETIME(UHeroAttributeComponent, JumpPower);
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
			MaxMoveSpeed = Data->MaxMoveSpeed;
			JumpPower = Data->JumpRate;
			AttackSpeedRate = Data->AttackSpeedRate;
			CriticalChance = Data->CriticalChance;
			CriticalDamageRate = Data->CriticalDamageRate;
		
			SkillQCurCoolTime = 0.0f;
			SkillECurCoolTime = 0.0f;
			SkillRCurCoolTime = 0.0f;
			SkillQMaxCoolTime = Data->SkillQInfo.CoolTime;
			SkillEMaxCoolTime = Data->SkillEInfo.CoolTime;
			SkillRMaxCoolTime = Data->SkillRInfo.CoolTime;
		}
	}
}

bool UHeroAttributeComponent::IsAttackCheck()
{
	return HasTagExact(TEXT("Character.State.NotAttackable"));
}
