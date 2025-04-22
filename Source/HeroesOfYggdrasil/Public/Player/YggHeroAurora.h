// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroAurora.generated.h"

/**
 * 
 */
class UNiagaraSystem;
class UNiagaraComponent;

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

	virtual void Attack(const FInputActionValue& Value) override;
	virtual void EndAttack(const FInputActionValue& Value) override;

	void Fly(const FInputActionValue& Value);

	virtual void SkillQ(const FInputActionValue& Value) override;
	virtual void SkillE(const FInputActionValue& Value) override;
	virtual void SkillR(const FInputActionValue& Value) override;

	virtual void Roll(const FInputActionValue& Value) override;

private:
	UPROPERTY()
	bool bIsSkillE = false;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* SkillRDecalMaterial;

	UPROPERTY()
	UDecalComponent* SkillRDecal;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillQAttackCapsuleComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillEAttackCapsuleComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillRAttackCapsuleComponent;
};
