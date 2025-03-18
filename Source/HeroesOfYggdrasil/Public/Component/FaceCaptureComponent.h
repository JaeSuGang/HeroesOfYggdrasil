// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneCaptureComponent2D.h"
#include "FaceCaptureComponent.generated.h"

class UTextureRenderTarget2D;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UFaceCaptureComponent : public USceneCaptureComponent2D
{
	GENERATED_BODY()
	

public:
	UFaceCaptureComponent();

	UFUNCTION(BlueprintCallable, Category = "YGG")
	UTextureRenderTarget2D* GetFaceRenderTarget() const
	{
		return RenderTarget;
	}

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "YGG")
	UTextureRenderTarget2D* RenderTarget;


};
