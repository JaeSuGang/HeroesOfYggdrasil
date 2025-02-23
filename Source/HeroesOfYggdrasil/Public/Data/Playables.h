#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Playables.generated.h"

USTRUCT(BlueprintType)
struct FPlayableCharacterRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PlayPawn;
};