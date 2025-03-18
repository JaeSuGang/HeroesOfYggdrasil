// Coded By AssortRock Unreal Engine Class Project


#include "Component/FaceCaptureComponent.h"
#include "Engine/TextureRenderTarget2D.h"

UFaceCaptureComponent::UFaceCaptureComponent()
{
	//RenderTarget = CreateDefaultSubobject<UTextureRenderTarget2D>(TEXT("FaceRenderTarget"));
	//
	//RenderTarget->InitAutoFormat(1024, 1024);
	//
	//TextureTarget = RenderTarget;



	/*SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("StatusCamera"));
	
	SceneCaptureComponent2D->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

	SceneCaptureComponent2D->ProjectionType = ECameraProjectionMode::Orthographic;
	SceneCaptureComponent2D->CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;
	SceneCaptureComponent2D->OrthoWidth = 300.0f;

	SceneCaptureComponent2D->AddRelativeLocation(FVector(100.f, 0.0f, 100.0f));
	SceneCaptureComponent2D->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));*/
}

void UFaceCaptureComponent::BeginPlay()
{
	Super::BeginPlay();


}
