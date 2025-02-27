// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroKhaimera.generated.h"



/**
 *	김성훈
 */

class UAnimMontage;

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroKhaimera : public AYggHero
{
	GENERATED_BODY()

public:
	AYggHeroKhaimera();
	

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Attack(const FInputActionValue& Value) override;

	virtual void Tick(float DeltaTime) override;
	virtual void Move(const FInputActionValue& Value) override;

	
	UFUNCTION(BlueprintCallable)
	void SaveAttack();
	UFUNCTION(BlueprintCallable)
	void ResetCombo();
	

	

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	TMap<FName,UAnimMontage*> MontageMap;


	bool bIsMoveable = true;
	bool bIsAttackable = true;
	int MaxCombo = 3;
	int CurCombo = 0;

	

};
