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


	virtual void SkillQ(const FInputActionValue& Value) override;
	UFUNCTION(Server, Reliable)
	void ServerSkillQ(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSkillQ(const FInputActionValue& Value);

	virtual void SkillE(const FInputActionValue& Value) override;
	UFUNCTION(Server, Reliable)
	void ServerSkillE(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSkillE(const FInputActionValue& Value);


	virtual void SkillR(const FInputActionValue& Value) override;
	UFUNCTION(Server, Reliable)
	void ServerSkillR(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSkillR(const FInputActionValue& Value);
	
};
