// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggStatusUserWidget.generated.h"

class UImage;
class UProgressBar;
class UTextBlock;
class UButton;
class UHeroAttributeComponent;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggStatusUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "YGG")
	void StatusInit();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void EndStatus();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void ShowAbility();

	//UFUNCTION(BlueprintCallable, Category = "YGG")
	//void EndAbility();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* Symbol;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Attack;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CriticalChance;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CriticalDamage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackSpeed;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Defense;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HP;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HPRegen;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityShowButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Symbol")
	UTexture2D* GreystoneSymbol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Symbol")
	UTexture2D* KhaimeraSymbol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Symbol")
	UTexture2D* RevenantSymbol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Symbol")
	UTexture2D* AuroraSymbol;

	UHeroAttributeComponent* HAC;

};
