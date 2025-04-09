// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomSystem/CustomSystem.h"
#include "UpgradeSystem.generated.h"

class UHeroAttributeComponent;
class UUpgradeDataAsset;

UCLASS()
class HEROESOFYGGDRASIL_API UUpgradeSystem : public UCustomSystem
{
	GENERATED_BODY()

public:	
	UUpgradeSystem();

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static UUpgradeSystem* Get(const UObject* WorldContextObject);

protected:
	virtual void BeginPlay() override;

public:
	/*
	* 플레이어의 선택지를 데이터 에셋으로 얻어냄
	* 오류 발생시 false 리턴
	*/
	UFUNCTION(BlueprintCallable)
	bool GetPlayerUpgradeChoicesAsDataAsset(APlayerController* PC, /* Out */ TArray<UUpgradeDataAsset*>& UpgradeChoices) const;

	/* 업그레이드 */
	UFUNCTION(BlueprintCallable)
	void Upgrade(UHeroAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RequestUpgrade(UHeroAttributeComponent* AttributeComponent, FPrimaryAssetId AssetId);
	void RequestUpgrade_Implementation(UHeroAttributeComponent* AttributeComponent, FPrimaryAssetId AssetId);

	UFUNCTION(BlueprintCallable)
	void UpgradeInternal(UHeroAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData);


	/* 업그레이드 선택지 생성 */
	UFUNCTION(BlueprintCallable)
	void GenerateUpgradeChoices(APlayerController* PC, int ChoiceCount);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RequestGenerateUpgradeChoices(APlayerController* PC, int ChoiceCount);

	UFUNCTION(BlueprintCallable)
	void GenerateUpgradeChoicesInternal(APlayerController* PC, int ChoiceCount);
};
