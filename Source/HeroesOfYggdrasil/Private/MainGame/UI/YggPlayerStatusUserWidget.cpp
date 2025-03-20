// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggPlayerStatusUserWidget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Component/CaptureComponent.h"
#include "Player/YggHero.h"


void UYggPlayerStatusUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    APlayerController* PC = GetOwningPlayer();
    
    if (true)
    {

    }

    AYggHero* PlayerCharacter = Cast<AYggHero>(PC->GetPawn());

    if (true)
    {

    }

    UTextureRenderTarget2D* RenderTarget = PlayerCharacter->GetFaceCaptureComponent()->GetRenderTarget();
    UTexture2D* CapturedTexture = ConvertRenderTargetToTexture2D(RenderTarget);

    if (CapturedTexture)
    {
       SetFaceCam(CapturedTexture);
    }
}

void UYggPlayerStatusUserWidget::SetFaceCam(UTexture2D* Texture)
{
    if (PlayerFace && Texture)
    {
        PlayerFace->SetBrushFromTexture(Texture);
    }
}

UTexture2D* UYggPlayerStatusUserWidget::ConvertRenderTargetToTexture2D(UTextureRenderTarget2D* RenderTarget)
{
    if (!RenderTarget) return nullptr;

    FTextureRenderTargetResource* RenderTargetResource = RenderTarget->GameThread_GetRenderTargetResource();
    if (!RenderTargetResource) return nullptr;

    return RenderTarget->ConstructTexture2D(this, TEXT("CapturedTexture"), EObjectFlags::RF_NoFlags);
}