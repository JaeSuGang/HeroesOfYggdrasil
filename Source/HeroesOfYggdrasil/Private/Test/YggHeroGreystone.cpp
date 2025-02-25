// Coded By AssortRock Unreal Engine Class Project

#include "Test/YggHeroGreystone.h"

AYggHeroGreystone::AYggHeroGreystone()
{
}

AYggHeroGreystone::~AYggHeroGreystone()
{
}

void AYggHeroGreystone::BeginPlay()
{
	Super::BeginPlay();
}

void AYggHeroGreystone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//
//void AYggHeroGreystone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//}

void AYggHeroGreystone::Attack(const FInputActionValue& _Value)
{
	Super::Attack(_Value);
}

void AYggHeroGreystone::SkillQ(const FInputActionValue& _Value)
{
	Super::SkillQ(_Value);

	UE_LOG(LogTemp, Warning, TEXT("SkiilQ"));
}

void AYggHeroGreystone::SkillE(const FInputActionValue& _Value)
{
	Super::SkillE(_Value);
}

void AYggHeroGreystone::SkillR(const FInputActionValue& _Value)
{
	Super::SkillR(_Value);
}
