// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"

#include "EnemyBaseAnimInstance.generated.h"

/**
 * 담당 : 장시혁
 */


class AEnemyCharacter;
class UCharacterMovementComponent;


UCLASS()
class HEROESOFYGGDRASIL_API UEnemyBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/*virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);*/

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))

	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;

	template<typename EnumType>
	void ChangeAnimation(EnumType _Animation, FName _SectionName = TEXT("None"))
	{
		return ChangeAnimation(static_cast<int>(_Animation), _SectionName);
	}

	int GetCurAnimationType()
	{
		return CurAnimationType;
	}


	void ChangeAnimation(int _Animation, FName _SectionName = TEXT("None"));

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeAnimationEvent(UAnimMontage* _Montage, FName _SectionName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeAnimationJumpEvent(UAnimMontage* _Montage, FName _SectionName);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAnimMontages")
	TMap<int, UAnimMontage*> AnimMontages;



protected:
	UPROPERTY(BlueprintReadOnly)
	AEnemyCharacter* Enemy;

	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly)
	float LocomotionDirection;

	// UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	// bool OwnerHaveTag(FGameplayTag _TagToCheck);

	UPROPERTY(BlueprintReadOnly)
	float RotationInterSpeed;


private:
	int CurAnimationType = 0;

	FName SectionName = TEXT("");

	UAnimMontage* CurMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;
};
