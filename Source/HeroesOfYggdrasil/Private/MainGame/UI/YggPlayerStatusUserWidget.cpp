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

    UTextureRenderTarget2D* RenderTarget = PlayerCharacter->GetFaceCaptureComponent()->GetTextureTarget();

    UTexture2D* CapturedTexture = ConvertRenderTargetToTexture2D(RenderTarget);

    SetFaceCam(CapturedTexture);
}

void UYggPlayerStatusUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

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

    UTextureRenderTarget2D* RenderTarget = PlayerCharacter->GetFaceCaptureComponent()->GetTextureTarget();
    
    UTexture2D* CapturedTexture = ConvertRenderTargetToTexture2D(RenderTarget);

    SetFaceCam(CapturedTexture);
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

    // 텍스처 데이터 복사
    TArray<FColor> Bitmap;
    RenderTargetResource->ReadPixels(Bitmap);

    int32 Width = RenderTarget->SizeX;
    int32 Height = RenderTarget->SizeY;

    // 새로운 UTexture2D 생성 (기존에 생성된 텍스처가 있으면 재사용)
    if (!Texture2D || Texture2D->GetPlatformData()->SizeX != Width || Texture2D->GetPlatformData()->SizeY != Height)
    {
        // 새 텍스처 생성
        Texture2D = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
        if (!Texture2D) return nullptr;
    }

    // 텍스처의 데이터 잠금
    void* TextureData = Texture2D->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
    if (!TextureData) return nullptr;

    // 텍스처 데이터 갱신
    FMemory::Memcpy(TextureData, Bitmap.GetData(), Bitmap.Num() * sizeof(FColor));

    // 텍스처 데이터 잠금 해제
    Texture2D->GetPlatformData()->Mips[0].BulkData.Unlock();

    // 텍스처 업데이트
    Texture2D->UpdateResource();

    return Texture2D;
}