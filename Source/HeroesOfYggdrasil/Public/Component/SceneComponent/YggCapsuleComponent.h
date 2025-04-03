// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "YggCapsuleComponent.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterType :uint8
{
	Player UMETA(DisplayName = "Player"),
	Monster UMETA(DisplayName = "Monster"),
};

UENUM(BlueprintType)
enum class EDamageType :uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Tick UMETA(DisplayName = "Tick"),
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HEROESOFYGGDRASIL_API UYggCapsuleComponent : public UCapsuleComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void CollisionOn();
	UFUNCTION(BlueprintCallable)
	virtual void CollisionOff();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UYggCapsuleComponent")
	ECharacterType CharacterType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UYggCapsuleComponent")
	EDamageType DamageType;

};
