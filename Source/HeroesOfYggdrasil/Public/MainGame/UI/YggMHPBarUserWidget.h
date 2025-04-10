// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggMHPBarUserWidget.generated.h"

class UProgressBar;
class AEnemyCharacter;
class UCharacterAttributeComponent;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggMHPBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeOnInitialized() override;
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateHPBar(float HP);

	UFUNCTION(BlueprintCallable)
	void Init(float HP);

	UFUNCTION(BlueprintCallable)
	void SetAttachedCharacter(AEnemyCharacter* Enemy);
	
	UPROPERTY()
	AEnemyCharacter* EnemyCharacter;
	
	UPROPERTY()
	UCharacterAttributeComponent* CAC;


	

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;
};
