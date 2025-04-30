// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/CharacterAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


void UCharacterAttributeComponent::Server_TakeDamage_Implementation(float fAmount)
{
	Server_SetHP(HP - fAmount);

	ServerDelegate_OnTakeDamage.Broadcast(fAmount);
	Client_TakeDamage(fAmount);
}

UCharacterAttributeComponent::UCharacterAttributeComponent()
{
	
}

void UCharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority())
	{
		FTimerHandle TH{};
		GetWorld()->GetTimerManager().SetTimer(TH, this, &UCharacterAttributeComponent::GenerateHpInternal, 1.0f, true);
	}
}

void UCharacterAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterAttributeComponent, HP);
	DOREPLIFETIME(UCharacterAttributeComponent, MaxHP);
	DOREPLIFETIME(UCharacterAttributeComponent, DefensePoints);
	DOREPLIFETIME(UCharacterAttributeComponent, AttackPoints);
	DOREPLIFETIME(UCharacterAttributeComponent, MaxMoveSpeed);
	DOREPLIFETIME(UCharacterAttributeComponent, AttackSpeedRate);
	DOREPLIFETIME(UCharacterAttributeComponent, HPGeneration);
	DOREPLIFETIME(UCharacterAttributeComponent, CriticalChance);
	DOREPLIFETIME(UCharacterAttributeComponent, CriticalDamageRate);
}

void UCharacterAttributeComponent::GenerateHpInternal()
{
	if (HPGeneration != 0 && HP > 0)
	{
		float HpToApply{};

		HpToApply = HP + HPGeneration > MaxHP ? MaxHP : HP + HPGeneration;

		Server_SetHP(HpToApply);
	}
}


float UCharacterAttributeComponent::GetHP() const
{
	return HP;
}

float UCharacterAttributeComponent::GetMaxHP() const
{
	return MaxHP;
}

float UCharacterAttributeComponent::GetDefensePoints() const
{
	return DefensePoints;
}

float UCharacterAttributeComponent::GetAttackPoints() const
{
	return AttackPoints;
}

float UCharacterAttributeComponent::GetMaxMoveSpeed() const
{
	return MaxMoveSpeed;
}

float UCharacterAttributeComponent::GetAttackSpeedRate() const
{
	return AttackSpeedRate;
}

void UCharacterAttributeComponent::Server_SetHPGeneration_Implementation(float fAmount)
{
	HPGeneration = fAmount;
	ServerDelegate_OnStatusChanged.Broadcast();
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		OnRep_Status();
	}
}

void UCharacterAttributeComponent::OnRep_Status()
{
	ClientDelegate_OnStatusChanged.Broadcast();
}

void UCharacterAttributeComponent::Server_SetDefensePoints_Implementation(float fAmount)
{
	DefensePoints = fAmount;

	ServerDelegate_OnStatusChanged.Broadcast();
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		OnRep_Status();
	}
}

void UCharacterAttributeComponent::Server_SetAttackSpeedRate_Implementation(float fAmount)
{
	AttackSpeedRate = fAmount;
	ServerDelegate_OnStatusChanged.Broadcast();
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		OnRep_Status();
	}
}

void UCharacterAttributeComponent::Server_SetMaxMoveSpeed_Implementation(float fAmount)
{
	MaxMoveSpeed = fAmount;

	ServerDelegate_OnStatusChanged.Broadcast();
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		OnRep_Status();
	}
}

void UCharacterAttributeComponent::Server_SetAttackPoints_Implementation(float fAmount)
{
	AttackPoints = fAmount;

	ServerDelegate_OnStatusChanged.Broadcast();
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		OnRep_Status();
	}
}

void UCharacterAttributeComponent::Server_SetMaxHP_Implementation(float fAmount)
{

	MaxHP = FMath::Clamp(fAmount, 1.0f, fAmount);

	ServerDelegate_OnStatusChanged.Broadcast();
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		OnRep_Status();
	}
}

void UCharacterAttributeComponent::Server_SetHP_Implementation(float fAmount)
{
	HP = fAmount;
	ServerDelegate_OnStatusChanged.Broadcast();
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		OnRep_Status();
	}
}

void UCharacterAttributeComponent::Client_TakeDamage_Implementation(float fAmount)
{
	ClientDelegate_OnTakeDamage.Broadcast(fAmount);
}
