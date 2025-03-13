// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YggConst.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggConst : public UObject
{
	GENERATED_BODY()
	
};

class CameraConst
{
public:
	static const float MaxCameraBoomLength;
	static const float MinCameraBoomLength;
	static const float ZoomSpeed;

	static const float NormalCameraBoomLength;
	static const float AimCameraBoomLength;

	static const FVector NormalSocketOffset;
	static const FVector AimSocketOffset;
};
