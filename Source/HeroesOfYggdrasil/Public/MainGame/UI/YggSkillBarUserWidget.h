// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "Data/YggStructData.h"
#include "YggSkillBarUserWidget.generated.h"


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
};
