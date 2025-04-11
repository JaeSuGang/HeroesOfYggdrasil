// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "Data/YggStructData.h"
#include "YggSkillBarUserWidget.generated.h"

class UProgressBar;
class UTexture2D;
class UTextBlock;

USTRUCT()
struct FSkillData
{
	GENERATED_BODY()

	UPROPERTY()
	UProgressBar* Bar = nullptr;

	UPROPERTY()
	UTexture2D* Icon = nullptr;

	UPROPERTY()
	UTextBlock* Text = nullptr;

	FTimerHandle TimerHandle;
	float CoolTime = 0.0f;
	float RemainingTime = 0.0f;
};

class UImage;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggSkillBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetSkillIcon(FName Character);

	//UFUNCTION(BlueprintCallable)
	//void SetIcon(UTexture2D* Q, UTexture2D* E, UTexture2D* R);
	
	UFUNCTION(BlueprintCallable)
	void SetTexture(UTexture2D* Q, UTexture2D* E, UTexture2D* R);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* SkillIcons;
	FSkillIcon* CharSkillIcon;

	UFUNCTION(BlueprintCallable)
	void InitSkills();

	UFUNCTION(BlueprintCallable)
	void SetupSkillBar(UProgressBar* Bar, UTexture2D* Tex, FVector2D Size);

	UFUNCTION(BlueprintCallable)
	void StartCoolTime(FName Key, float Duration);

	UFUNCTION(BlueprintCallable)
	void UpdateCoolTime(FName Key);

	UFUNCTION(BlueprintCallable)
	void EndCoolTime(FName Key);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;


private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Skill_Q;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Skill_E;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Skill_R;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* Skill_Shift;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoolTimeQ;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoolTimeE;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoolTimeR;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoolTimeShift;

	UTexture2D* QTexture;
	UTexture2D* ETexture;
	UTexture2D* RTexture;
	UTexture2D* ShiftTexture;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UMaterialInterface* DiamondMaskMaterial;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UTexture2D* DiamondMaskTexture;

	//UPROPERTY()
	//UMaterialInstanceDynamic* SkillMatInst;
	UPROPERTY()
	TMap<FName, FSkillData> SkillMap;

	UPROPERTY()
	TMap<UProgressBar*, UMaterialInstanceDynamic*> MaterialMap;
};
