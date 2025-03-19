// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttackInterface : public UInterface
{
	GENERATED_BODY()

public:
	UAttackInterface(class FObjectInitializer const& _Object);
};

/**
 * 
 */
class HEROESOFYGGDRASIL_API IAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AttackUpdate(float _DeltaTime);
	virtual void AttackStart();
	virtual void AttackEnd();
};
