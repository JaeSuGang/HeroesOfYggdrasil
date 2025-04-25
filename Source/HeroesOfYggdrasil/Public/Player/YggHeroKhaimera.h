// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroKhaimera.generated.h"



/**
 *	김성훈
 */

class UYggCapsuleComponent;

class UYggParticleSystemComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroKhaimera : public AYggHero
{
	GENERATED_BODY()

public:
	AYggHeroKhaimera();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime)override;

	virtual FName GetHeroName() const override { return FName(TEXT("Khaimera")); };
	virtual void SkillQ(const FInputActionValue& Value);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> NormalAttackCapsuleComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillQAttackAttackCapsuleComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillEAttackAttackCapsuleComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "YggHero")
	TObjectPtr<class UYggAttackCapsuleComponent> SkillRAttackAttackCapsuleComponent;



};
