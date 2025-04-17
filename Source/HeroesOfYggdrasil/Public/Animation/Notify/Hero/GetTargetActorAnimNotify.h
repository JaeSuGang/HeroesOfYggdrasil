// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GetTargetActorAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UGetTargetActorAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggHeroRevenant")
	float Scope;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggHeroRevenant")
	TSubclassOf<class AYggBombActor> BombClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYggHeroRevenant")
	FName SocketName;
	
};
