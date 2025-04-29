// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "StageSystem/StageSystem.h"

#include "YggBossHPBarUserWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UCharacterAttributeComponent;
class AEnemyManager;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggBossHPBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = YGG)
	void UpdateWidget();

	UFUNCTION(BlueprintCallable, Category = YGG)
	void Init(AEnemyManager* EnemyManager);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPText;

	UCharacterAttributeComponent* CAC;
};
