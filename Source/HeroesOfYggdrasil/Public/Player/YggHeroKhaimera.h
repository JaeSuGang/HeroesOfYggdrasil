// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroKhaimera.generated.h"



/**
 *	김성훈
 */

class UYggCapsuleComponent;

class UYggParticleSystemComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroKhaimera : public AYggHero
{
	GENERATED_BODY()

public:
	AYggHeroKhaimera();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;

	
	
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

protected:
	

};
