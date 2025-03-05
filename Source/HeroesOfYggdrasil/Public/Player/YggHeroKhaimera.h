// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroKhaimera.generated.h"



/**
 *	김성훈
 */




UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroKhaimera : public AYggHero
{
	GENERATED_BODY()

public:
	AYggHeroKhaimera();

	UFUNCTION(BlueprintCallable)
	void SaveAttack();
	UFUNCTION(BlueprintCallable)
	void ResetCombo();


protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay()override;

	virtual void Attack(const FInputActionValue& Value) override;
	UFUNCTION(Server, Reliable)
	void ServerAttack();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastAttack(int NewCurCombo);
	
	virtual void SkillQ(const FInputActionValue& Value) override;
	UFUNCTION(Server, Reliable)
	void ServerSkillQ();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSkillQ();

	virtual void SkillE(const FInputActionValue& Value) override;
	UFUNCTION(Server, Reliable)
	void ServerSkillE();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSkillE();


	virtual void SkillR(const FInputActionValue& Value) override;
	UFUNCTION(Server, Reliable)
	void ServerSkillR();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSkillR();


	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	

	
};
