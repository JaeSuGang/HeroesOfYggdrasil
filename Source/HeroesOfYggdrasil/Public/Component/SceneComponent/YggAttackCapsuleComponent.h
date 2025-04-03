// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Component/SceneComponent/YggCapsuleComponent.h"
#include "Data/YggStructData.h"
#include "YggAttackCapsuleComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	SkillQ UMETA(DisplayName = "SkillQ"),
	SkillE UMETA(DisplayName = "SkillE"),
	SkillR UMETA(DisplayName = "SkillR")
};

UCLASS()
class HEROESOFYGGDRASIL_API UYggAttackCapsuleComponent : public UYggCapsuleComponent
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OverLapTick(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void BeginPlay() override;

	virtual void CollisionOn() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType AttackType;
};
