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
class AEnemyManager;
class UWidgetAnimation;

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
	void UpdateStatus();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void ShowStatus();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void EndStatus();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void ShowAbility();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	UTexture2D* SetTexture(FName Hero);

	UFUNCTION(BlueprintCallable, Category = "YGG")
	FSlateBrush MakeBrush(UTexture2D* Tex, FVector2D Size, float Brightness = 1.0f);

	//UFUNCTION(BlueprintCallable, Category = "YGG")
	//void EndAbility();

	//UFUNCTION(BlueprintCallable, Category = "YGG")
	//void UpdateDebuffUI(FOnTagsChangedParams OnTagsChangedParams);
	// 
	//UFUNCTION(BlueprintCallable, Category = "YGG")
	//void DragStart();
	//
	//UFUNCTION(BlueprintCallable, Category = "YGG")
	//void DragEnd();


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


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
	UTextBlock* Health;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthRegen;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HP;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Nickname;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MoveSpeed;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UButton* AbilityShowButton;

	UPROPERTY(EditAnywhere, Category = "Symbol")
	UTexture2D* GreystoneSymbol;

	UPROPERTY(EditAnywhere, Category = "Symbol")
	UTexture2D* KhaimeraSymbol;

	UPROPERTY(EditAnywhere, Category = "Symbol")
	UTexture2D* RevenantSymbol;

	UPROPERTY(EditAnywhere, Category = "Symbol")
	UTexture2D* AuroraSymbol;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* PopupAnim;

	UHeroAttributeComponent* HAC;

	//bool IsDrag = false;
	//
	//FVector2D DragOffset;

};
