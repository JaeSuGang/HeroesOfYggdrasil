// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMiniMapUserWidget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Component/CaptureComponent.h"
#include "Player/YggHero.h"


void UYggMiniMapUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    SetMiniMapCam();
}

void UYggMiniMapUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    SetMiniMapCam();
}

void UYggMiniMapUserWidget::SetMiniMapCam()
{
    if (!MiniMap || !MaskedMaterial || !CircleMaskTexture)
    {
        UE_LOG(LogTemp, Warning, TEXT("SetFaceCam: 필요한 리소스가 없습니다."));
        return;
    }

    APlayerController* PC = GetOwningPlayer();

    if (nullptr == PC)
    {
        UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == PC)"), __FUNCTION__, __LINE__);
        return;
    }

    AYggHero* PlayerCharacter = Cast<AYggHero>(PC->GetPawn());

    if (nullptr == PlayerCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == PlayerCharacter)"), __FUNCTION__, __LINE__);
        return;
    }

    UTextureRenderTarget2D* RenderTarget = PlayerCharacter->GetMiniMapCaptureComponent()->GetTextureTarget();

    if (!MiniMapMatInst)
    {
        MiniMapMatInst = UMaterialInstanceDynamic::Create(MaskedMaterial, this);
    }

    MiniMapMatInst->SetTextureParameterValue("RenderTarget", RenderTarget);
    MiniMapMatInst->SetTextureParameterValue("CircleMaskTexture", CircleMaskTexture);

    FSlateBrush Brush;
    Brush.SetResourceObject(MiniMapMatInst);
    Brush.ImageSize = FVector2D(320.f, 320.f);
    MiniMap->SetBrush(Brush);
}