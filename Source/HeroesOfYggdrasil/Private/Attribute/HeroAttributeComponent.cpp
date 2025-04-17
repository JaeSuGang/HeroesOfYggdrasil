// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/HeroAttributeComponent.h"
#include "Engine/DataTable.h"
#include "Net/UnrealNetwork.h"

#include "Data/YggStructData.h"
#include "Player/YggHero.h"
#include "GameFramework/CharacterMovementComponent.h"

UHeroAttributeComponent::UHeroAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHeroAttributeComponent::BeginPlay()
{
    Super::BeginPlay();   
	ClientDelegate_OnStatusChanged.AddDynamic(this, &UHeroAttributeComponent::UpdateStatus);
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
}

void UHeroAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UHeroAttributeComponent, JumpPower);
	DOREPLIFETIME(UHeroAttributeComponent, CriticalChance);
	DOREPLIFETIME(UHeroAttributeComponent, CriticalDamageRate);
}

void UHeroAttributeComponent::UpdateStatus()
{
	AYggHero* Hero = Cast<AYggHero>(GetOwner());
	if (IsValid(Hero))
	{
		Hero->GetCharacterMovement()->JumpZVelocity = JumpPower;
		Hero->GetCharacterMovement()->MaxWalkSpeed = MaxMoveSpeed;
	}
}

void UHeroAttributeComponent::ServerSetBaseData_Implementation(const FName& Name)
{
	if (BaseData)
	{
		FHeroBaseStatusInfoRow* Data = BaseData->FindRow<FHeroBaseStatusInfoRow>(Name, nullptr);
		if (Data)
		{
			HeroName = Name;
			MaxHP = Data->MaxHP;
			HP = MaxHP;
			MaxMoveSpeed = Data->MaxMoveSpeed;
			JumpPower = Data->JumpRate;
			AttackPoints = Data->AttPower;
			AttackSpeedRate = Data->AttackSpeedRate;
			CriticalChance = Data->CriticalChance;
			CriticalDamageRate = Data->CriticalDamageRate;
		
			SkillQInfo = Data->SkillQInfo;
			SkillEInfo = Data->SkillEInfo;
			SkillRInfo = Data->SkillRInfo;

			SkillQCurCoolTime = 0.0f;
			SkillECurCoolTime = 0.0f;
			SkillRCurCoolTime = 0.0f;
			SkillQMaxCoolTime = Data->SkillQInfo.CoolTime;
			SkillEMaxCoolTime = Data->SkillEInfo.CoolTime;
			SkillRMaxCoolTime = Data->SkillRInfo.CoolTime;

			SkillQCurContinueTime = 0.0f;
			SkillECurContinueTime = 0.0f;
			SkillRCurContinueTime = 0.0f;
			SkillQMaxContinueTime = Data->SkillQInfo.ContinueTime;
			SkillEMaxContinueTime = Data->SkillEInfo.ContinueTime;
			SkillRMaxContinueTime = Data->SkillRInfo.ContinueTime;
		}
	}
}

bool UHeroAttributeComponent::IsAttackCheck()
{
	return HasTagExact(TEXT("Character.State.NotAttackable"));
}
