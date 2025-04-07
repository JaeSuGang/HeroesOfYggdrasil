// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "Data/YggStructData.h"
#include "YggSkillBarUserWidget.generated.h"

class UProgressBar;
class UTexture2D;

USTRUCT()
struct FSkillData
{
	GENERATED_BODY()

	UPROPERTY()
	UProgressBar* Bar = nullptr;

	UPROPERTY()
	UTexture2D* Icon = nullptr;

	/*UPROPERTY()
	float CooldownDuration = 0.0f;*/

	/*float RemainingTime = 0.0f;*/
	FTimerHandle TimerHandle;
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

	UFUNCTION(BlueprintCallable)
	void SetIcon(UTexture2D* Q, UTexture2D* E, UTexture2D* R);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* SkillIcons;
	FSkillIcon* CharSkillIcon;

	void SetTexture(UTexture2D* Q, UTexture2D* E, UTexture2D* R);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;


private:
	UPROPERTY(meta = (BindWidget))
	UImage* Skill_Q;
	UPROPERTY(meta = (BindWidget))
	UImage* Skill_E;
	UPROPERTY(meta = (BindWidget))
	UImage* Skill_R;
	UPROPERTY(meta = (BindWidget))
	UImage* Skill_Shift;

	UTexture2D* SkillQ;
	UTexture2D* SkillE;
	UTexture2D* SkillR;
	UTexture2D* SkillShift;


	TMap<FName, FSkillData> SkillMap;
};
