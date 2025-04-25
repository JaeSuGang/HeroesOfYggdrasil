// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroAurora.generated.h"

/**
 * 
 */

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroAurora : public AYggHero
{
	GENERATED_BODY()
	AYggHeroAurora();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Look(const FInputActionValue& Value) override;
	virtual void Roll(const FInputActionValue& Value) override;

	virtual void Attack(const FInputActionValue& Value) override;
	virtual void EndAttack(const FInputActionValue& Value) override;

	virtual void SkillQ(const FInputActionValue& Value) override;
	virtual void SkillE(const FInputActionValue& Value) override;
	virtual void SkillR(const FInputActionValue& Value) override;


	virtual void Jump() override;

public:
	void MagicCircleOn();
	void MagicCircleOff();

private:
	UPROPERTY()
	bool bIsSkillE = false;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* SkillEDecalMaterial;

	UPROPERTY()
	UDecalComponent* SkillEDecal;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillQAttackCapsuleComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillEAttackCapsuleComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillRAttackCapsuleComponent;

	/** 최대 제트팩 연료량(초 단위) */
	float MaxJetpackFuel = 5.0f;
	/** 현재 남은 연료량 */
	float CurrentFuel = MaxJetpackFuel;
	/** 제트팩 추진력 (Upward Acceleration) */
	float JetpackThrust = 2000.0f;
	/** 연료 소모 속도 (초당) */
	float FuelConsumptionRate = 1.5f;
	/** 연료 충전 속도 (초당) */
	float FuelRechargeRate = 0.5f;
	/** 제트팩 사용 중 플래그 */
	bool bIsJetpacking = false;

	UFUNCTION()
	void JetpackOn(const FInputActionValue& Value);
	UFUNCTION()
	void JetpackOff(const FInputActionValue& Value);
};
