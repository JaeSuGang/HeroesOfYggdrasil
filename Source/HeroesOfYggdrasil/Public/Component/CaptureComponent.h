// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "CaptureComponent.generated.h"

class UTextureRenderTarget2D;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UCaptureComponent : public USceneCaptureComponent2D
{
	GENERATED_BODY()
	

public:
	UCaptureComponent();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	UTextureRenderTarget2D* GetTextureTarget() const
	{
		return TextureTarget;
	}

	void SetupFaceCapture(AActor* TargetActor);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

		
};
