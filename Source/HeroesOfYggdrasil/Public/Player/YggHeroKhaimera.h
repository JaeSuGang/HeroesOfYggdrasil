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
	virtual void Attack(const FInputActionValue& _Value) override;

	UPROPERTY(EditDefaultsOnly, Category = "Montage")
	TMap<FName,UAnimMontage*> MontageMap;

	bool bIsAnimPlaying = false;
	int MaxCombo = 3;
	int CurCombo = 0;
};
