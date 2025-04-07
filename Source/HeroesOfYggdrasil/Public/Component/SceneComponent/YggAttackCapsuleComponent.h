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
enum class EDamageType :uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Tick UMETA(DisplayName = "Tick"),
};

UENUM(BlueprintType)
enum class ECharacterType :uint8
{
	Hero UMETA(DisplayName = "Hero"),
	Enemy UMETA(DisplayName = "Enemy"),
};

UENUM(BlueprintType)
enum class EAttackType :uint8
{
	None UMETA(DisplayName = "None"),
	Normal UMETA(DisplayName = "Attack"),
	SkillQ UMETA(DisplayName = "SkillQ"),
	SkillE UMETA(DisplayName = "SkillE"),
	SkillR UMETA(DisplayName = "SkillR"),
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HEROESOFYGGDRASIL_API UYggAttackCapsuleComponent : public UYggCapsuleComponent
{
	GENERATED_BODY()
public:
	UYggAttackCapsuleComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	virtual void OverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OverLapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void CollisionOn() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Coefficient;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> OverlappedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECharacterType CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackType AttackType;

	float CurTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayTime;
};
