// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YggCharacter.generated.h"


class UCharacterAttributeComponent;
class UYggAttackCapsuleComponent;

UCLASS()
class HEROESOFYGGDRASIL_API AYggCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AYggCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual UCharacterAttributeComponent* GetAttributeComponent() { return CharacterAttributeComponent; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UYggAttackCapsuleComponent* GetAttackCapsuleComponent(const FName& Key);

protected:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	UCharacterAttributeComponent* CharacterAttributeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, UYggAttackCapsuleComponent*> AttackCapsuleComponentMap;

	
};
