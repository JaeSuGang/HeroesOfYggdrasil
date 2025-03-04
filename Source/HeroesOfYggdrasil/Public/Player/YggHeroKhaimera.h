// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroKhaimera.generated.h"



/**
 *	김성훈
 */

class UAnimMontage;
class UAttributeComponent;

struct FGamePlayTag;

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroKhaimera : public AYggHero
{
	GENERATED_BODY()

public:
	AYggHeroKhaimera();


protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay()override;

	virtual void Attack(const FInputActionValue& Value) override;

	virtual void SkillQ(const FInputActionValue& Value) override;
	virtual void SkillE(const FInputActionValue& Value) override;
	virtual void SkillR(const FInputActionValue& Value) override;

	virtual void Move(const FInputActionValue& Value) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UFUNCTION(BlueprintCallable,Reliable,Server)
	void SaveAttack();
	UFUNCTION(BlueprintCallable, Reliable, Server)
	void ResetCombo();

	int MaxCombo = 3;
	UPROPERTY(Replicated)
	int CurCombo = 0;
};
