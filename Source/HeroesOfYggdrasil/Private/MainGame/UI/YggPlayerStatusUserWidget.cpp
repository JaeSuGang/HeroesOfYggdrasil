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

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    AYggHero* Pawn = PC->GetPawn<AYggHero>();

    UCharacterAttributeComponent* CAC =  Pawn->GetAttributeComponent();

    //CAC->HasTag("Character.Debuff." + EStatusEffectType::Poison);


    //HPBarUserWidget = CreateWidget<UYggHPBarUserWidget>(GetWorld(), HPBarWidgetClass);
    //if (!HPBarUserWidget)
    //    UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
    //
    //if (!VerticalBox)
    //    UE_LOG(LogTemp, Warning, TEXT("%S (%u) VerticalBox가 nullptr임"), __FUNCTION__, __LINE__);
    //
    //
    //UVerticalBoxSlot* HPBarSlot = VerticalBox->AddChildToVerticalBox(HPBarUserWidget);
    //
    //HPBarSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
    //HPBarSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
    
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