// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroRevenant.generated.h"


/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroRevenant : public AYggHero
{
	GENERATED_BODY()
public:
	AYggHeroRevenant();
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

	virtual void Attack(const FInputActionValue& Value) override;

	virtual void SkillQ(const FInputActionValue& Value) override;
	virtual void SkillE(const FInputActionValue& Value) override;
	virtual void SkillR(const FInputActionValue& Value) override;


public:
	

protected:



	
};
