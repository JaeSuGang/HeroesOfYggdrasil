// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "UpgradeManager.generated.h"

class UUpgradeDataAsset;
class UHeroAttributeComponent;

/**
 * 담당 코더 : 김경민
 */
UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API AUpgradeManager : public AInfo
{
	GENERATED_BODY()
	
public:
	AUpgradeManager();

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static AUpgradeManager* Get(UObject* WorldContextObject);

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
	void RequestUpgrade(AActor* AttributeOwner, FPrimaryAssetId AssetId);

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
