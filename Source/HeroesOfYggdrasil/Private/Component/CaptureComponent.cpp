// Coded By AssortRock Unreal Engine Class Project


#include "Component/CaptureComponent.h"
#include "Engine/TextureRenderTarget2D.h"

UCaptureComponent::UCaptureComponent()
{
	RenderTarget = NewObject<UTextureRenderTarget2D>();

	RenderTarget->InitAutoFormat(1024, 1024);

	PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;
	ProjectionType = ECameraProjectionMode::Orthographic;
	CaptureSource = ESceneCaptureSource::SCS_FinalColorLDR;

	TextureTarget = RenderTarget;

	bCaptureEveryFrame = true;
	bCaptureOnMovement = true;

	OrthoWidth = 50.0f;
}

void UCaptureComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCaptureComponent::SetupFaceCapture(AActor* TargetActor)
{
	if (!TargetActor) return;

	// 기존 목록 초기화
	ShowOnlyActors.Empty();

	// 타겟 액터만 캡처하도록 설정
	ShowOnlyActors.Add(TargetActor);

	// 캡처 강제 업데이트
	CaptureScene();
}

void UCaptureComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 매 프레임 캡처 보장
	CaptureScene();
}