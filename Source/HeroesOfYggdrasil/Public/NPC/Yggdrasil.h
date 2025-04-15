// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "NPC/YggNPC.h"
#include "Yggdrasil.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggdrasil : public AYggNPC
{
	GENERATED_BODY()
	
public:
	AYggdrasil();

	virtual void Tick(float DeltaTime) override;

};
