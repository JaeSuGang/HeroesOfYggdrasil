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

	void Fly(const FInputActionValue& Value);
};
