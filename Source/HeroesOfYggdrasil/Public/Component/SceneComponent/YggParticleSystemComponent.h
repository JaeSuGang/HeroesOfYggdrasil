// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "YggParticleSystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggParticleSystemComponent : public UParticleSystemComponent
{
	GENERATED_BODY()
	
public:
	virtual void ParticleOn();
	virtual void ParticleOff();
};
