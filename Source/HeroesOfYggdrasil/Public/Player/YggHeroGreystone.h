// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "Interfaces/YggHeroInterface.h"
#include "YggHeroGreystone.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroGreystone : public AYggHero, public IYggHeroInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void Look(const FInputActionValue& Value) override;	
	virtual void Move(const FInputActionValue& Value) override;
	void Jump(const FInputActionValue& Value);

	virtual void Attack(const FInputActionValue& Value) override;
	UFUNCTION(Server, Reliable)
	void ServerAttack();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastAttack(int ServerAttackIndex);

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

public:
	AYggHeroGreystone();
	~AYggHeroGreystone();

	virtual void MagicCircleOn() override;
	virtual void MagicCircleOff() override;

	UPROPERTY()
	bool bIsSkillR = false;

private:
	UPROPERTY(EditAnywhere)
	UMaterialInterface* SkillRDecalMaterial;

	UPROPERTY()
	UDecalComponent* SkillRDecal;
};