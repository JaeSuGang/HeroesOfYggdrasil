// Coded By AssortRock Unreal Engine Class Project


#include "Component/CaptureComponent.h"
#include "Engine/TextureRenderTarget2D.h"

UCaptureComponent::UCaptureComponent()
{
	RenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("FaceRenderTarget"));
	
	RenderTarget->InitAutoFormat(1024, 1024);
	
	PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	ProjectionType = ECameraProjectionMode::Orthographic;
	CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	OrthoWidth = 100.0f;

	TextureTarget = RenderTarget;

	bCaptureEveryFrame = true;


	/*SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("StatusCamera"));
	
	SceneCaptureComponent2D->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

	SceneCaptureComponent2D->ProjectionType = ECameraProjectionMode::Orthographic;
	SceneCaptureComponent2D->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	SceneCaptureComponent2D->OrthoWidth = 300.0f;

	SceneCaptureComponent2D->AddRelativeLocation(FVector(100.f, 0.0f, 100.0f));
	SceneCaptureComponent2D->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));*/
}

void UCaptureComponent::BeginPlay()
{
	Super::BeginPlay();


}
