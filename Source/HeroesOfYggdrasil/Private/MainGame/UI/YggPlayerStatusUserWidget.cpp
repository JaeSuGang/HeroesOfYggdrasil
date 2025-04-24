// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggPlayerStatusUserWidget.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Component/CaptureComponent.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "Player/YggHero.h"
#include "MainGame/UI/YggHPBarUserWidget.h"
#include "MainGame/UI/YggNicknameBarUserWidget.h"
#include "Data/YggEnumData.h"


void UYggPlayerStatusUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    SetFaceCam();

}

void UYggPlayerStatusUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    SetFaceCam();
}

void UYggPlayerStatusUserWidget::SetFaceCam()
{
    if (!PlayerFace || !MaskedMaterial || !DiamondMaskTexture)
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

    UTextureRenderTarget2D* RenderTarget = PlayerCharacter->GetFaceCaptureComponent()->GetTextureTarget();

    if (!FaceMatInst)
    {
        FaceMatInst = UMaterialInstanceDynamic::Create(MaskedMaterial, this);
    }

    FaceMatInst->SetTextureParameterValue("RenderTarget", RenderTarget);
    FaceMatInst->SetTextureParameterValue("DiamondMaskTexture", DiamondMaskTexture);
    
    FSlateBrush Brush;
    Brush.SetResourceObject(FaceMatInst);
    Brush.ImageSize = FVector2D(128.f, 128.f);
    PlayerFace->SetBrush(Brush);
}