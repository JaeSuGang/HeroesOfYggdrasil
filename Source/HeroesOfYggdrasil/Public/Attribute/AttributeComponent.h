// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROESOFYGGDRASIL_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer Status;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, float> Values;


	// 김성훈- 추가
	UFUNCTION(BlueprintCallable)
	bool HasStatusTag(const FName& Tag);

	UFUNCTION(BlueprintCallable)
	void AddStatusTag(const FName& Tag);
	UFUNCTION(BlueprintCallable)
	void AddStatusTags(const TArray<FName>& Tags);

	UFUNCTION(BlueprintCallable)
	void RemoveStatusTag(const FName& Tag);
	UFUNCTION(BlueprintCallable)
	void RemoveStatusTags(const TArray<FName>& Tags);

	

};
