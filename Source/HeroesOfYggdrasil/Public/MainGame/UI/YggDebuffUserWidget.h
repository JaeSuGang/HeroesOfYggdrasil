// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "Data/YggEnumData.h"
#include "YggDebuffUserWidget.generated.h"

class UProgressBar;
class UImage;
class UTexture2D;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggDebuffUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "YGG")
	void InitDebuff(EStatusEffectType StatusEffectType);

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void StartDebuff(float Duration);

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void UpdateDebuffBar();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void EndDebuff();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	UTexture2D* SetTexture(EStatusEffectType StatusEffectType);

	EStatusEffectType GetDebuffType()
	{
		return DebuffType;
	}

	FTimerHandle TimerHandle;
	float DebufflTime = 0.0f;
	float RemainingTime = 0.0f;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


private:
	UPROPERTY(meta = (BindeWidget))
	UProgressBar* DebuffBar;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UTexture2D* PosionTexture;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UTexture2D* BurnTexture;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UTexture2D* SlowTexture;

	UPROPERTY(EditAnywhere, Category = "YGG")
	UTexture2D* StunnedTexture;

	UTexture2D* Tex;

	EStatusEffectType DebuffType;
};
