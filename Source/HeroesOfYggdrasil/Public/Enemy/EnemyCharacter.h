
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/YggCharacter.h"
#include "Enemy/EnemyAnimCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 담당 : 장시혁
 */

class UCharacterAttributeComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AEnemyCharacter : public AEnemyAnimCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	UCharacterAttributeComponent* EnemyAttributeComponent;
};
