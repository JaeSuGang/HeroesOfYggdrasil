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
	void StartDebuff();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void UpdateDebuffBar(float Durtion);

	UFUNCTION(BlueprintCallable, Category = "YGG")
	void EndDebuff();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	UTexture2D* SetTexture(EStatusEffectType StatusEffectType);

	UFUNCTION(BlueprintCallable, Category = "YGG")
	FSlateBrush MakeTexBrush(UTexture2D* Tex, FVector2D Size, float Brightness = 1.0f);

	EStatusEffectType GetDebuffType()
	{
		return DebuffType;
	}

	FTimerHandle TimerHandle;
	float DebuffTime = 0.0f;
	float RemainingTime = 0.0f;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

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

	UTexture2D* Texture;

	EStatusEffectType DebuffType;
};
