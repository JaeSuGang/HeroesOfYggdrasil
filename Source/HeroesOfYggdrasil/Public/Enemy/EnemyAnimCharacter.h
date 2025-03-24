// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggCharacter.h"
#include "Animation/EnemyBaseAnimInstance.h"
#include "EnemyAnimCharacter.generated.h"

/**
 * 
 */

class UEnemyBaseAnimInstance;

UCLASS()
class HEROESOFYGGDRASIL_API AEnemyAnimCharacter : public AYggCharacter
{
	GENERATED_BODY()
	
public:

	AEnemyAnimCharacter();

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
	void ChangeAnimation_Multicast(int _CurAnimnation, FName _SectionName = TEXT("None"));
	void ChangeAnimation_Multicast_Implementation(int _CurAnimnation, FName _SectionName = TEXT("None"));

	UEnemyBaseAnimInstance* GetEnemyAnimInstance()
	{
		return EnemyBaseAnimInstance;;
	}

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UEnemyBaseAnimInstance* EnemyBaseAnimInstance = nullptr;
};
