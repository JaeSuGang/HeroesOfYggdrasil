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

};
