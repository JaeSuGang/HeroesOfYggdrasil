// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Player/YggHero.h"
#include "YggHeroRevenant.generated.h"


/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroRevenant : public AYggHero
{
	GENERATED_BODY()
public:
	AYggHeroRevenant();
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

	virtual void Attack(const FInputActionValue& Value) override;


	virtual void SkillQ(const FInputActionValue& Value) override;
	virtual void SkillE(const FInputActionValue& Value) override;

	UFUNCTION(Server, Reliable)
	void ServerAttackRevenant(const FInputActionValue& Value);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastAttackRevenant(const FInputActionValue& Value);

public:
	UFUNCTION(Server, Reliable)
	void Server_SetPendingAimDirection(const FVector& InAimDir);
	UFUNCTION()
	FVector Local_SetPendingAimDirection();

	UPROPERTY(Replicated)
	FVector AimDirection;
	/*virtual void SkillR(const FInputActionValue& Value) override;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggHeroRevenant")
	TSubclassOf<class AYggProjectileActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggHeroRevenant")
	FName SocketName;
	




};
