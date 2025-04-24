// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AttributeComponent.generated.h"

USTRUCT()
struct FOnTagsChangedParams
{
	GENERATED_BODY()


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagsChanged, FOnTagsChangedParams, OnTagsChangedParams);

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();

protected:
	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
public:
	UFUNCTION(BlueprintCallable)
	bool HasTag(const FName& Tag);

	UFUNCTION(BlueprintCallable)
	bool HasTagExact(const FName& Tag);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AddTag(const FName& Tag);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AddTags(const TArray<FName>& Tags);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RemoveTag(const FName& Tag);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RemoveTags(const TArray<FName>& Tags);

public:
	UPROPERTY()
	FOnTagsChanged OnTagsChanged;

public:
	UFUNCTION()
	void OnRep_Tags();

//protected:
	UPROPERTY(ReplicatedUsing=OnRep_Tags, EditAnywhere)
	FGameplayTagContainer GameplayTags;
};
