// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SpawnProjetileAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API USpawnProjetileAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggHeroRevenant")
	TSubclassOf<class AYggProjectileActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggHeroRevenant")
	FName SocketName;
};
