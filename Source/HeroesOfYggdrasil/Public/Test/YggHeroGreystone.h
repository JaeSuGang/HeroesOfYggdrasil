// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroGreystone.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroGreystone : public AYggHero
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Attack(const FInputActionValue& _Value) override;
	virtual void SkillQ(const FInputActionValue& _Value) override;
	virtual void SkillE(const FInputActionValue& _Value) override;
	virtual void SkillR(const FInputActionValue& _Value) override;

public:
	AYggHeroGreystone();
	~AYggHeroGreystone();
};
