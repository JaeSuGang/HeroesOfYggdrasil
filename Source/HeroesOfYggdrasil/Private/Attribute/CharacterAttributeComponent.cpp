// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/CharacterAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"


void UCharacterAttributeComponent::Server_TakeDamage_Implementation(float fAmount)
{
	HP -= fAmount;

	ServerDelegate_OnTakeDamage.Broadcast(fAmount);
	Client_TakeDamage(fAmount);
}

UCharacterAttributeComponent::UCharacterAttributeComponent()
{
	
}

void UCharacterAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

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

void UCharacterAttributeComponent::OnRep_Status()
{
	ClientDelegate_OnStatusChanged.Broadcast();
}

void UCharacterAttributeComponent::Server_SetDefensePoints_Implementation(float fAmount)
{
	DefensePoints = fAmount;

	ServerDelegate_OnStatusChanged.Broadcast();
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
	MaxHP = fAmount;

	ServerDelegate_OnStatusChanged.Broadcast();
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		OnRep_Status();
	}
}

void UCharacterAttributeComponent::Server_SetHP_Implementation(float fAmount)
{
	HP = fAmount;
}

void UCharacterAttributeComponent::Client_TakeDamage_Implementation(float fAmount)
{
	ClientDelegate_OnTakeDamage.Broadcast(fAmount);
}


