// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggSkillBarUserWidget.h"
//#include "Data/YggStructData.h"
//#include "Engine/Texture2D.h"

#include "Components/Image.h"


void UYggSkillBarUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    
}

void UYggSkillBarUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        if (APawn* Pawn = PC->GetPawn())
        {
            FString FullClassName = Pawn->GetClass()->GetName(); // ex: "BP_YggHeroGreystone_C"

            // "_C" 제거
            FString CleanName;
            FullClassName.Split(TEXT("_C"), &CleanName, nullptr); // 결과: "BP_YggHeroGreystone"

            // "BP_YggHero" 다음의 이름 추출
            FString HeroName;
            CleanName.Split(TEXT("BP_YggHero"), nullptr, &HeroName); // 결과: "Greystone"

            SetSkillIcon(FName(HeroName));
        }
    }
}

void UYggSkillBarUserWidget::SetSkillIcon(FName Character)
{
    if (!SkillIcons) return;

    CharSkillIcon = SkillIcons->FindRow<FSkillIcon>(Character, nullptr);

    if (CharSkillIcon)
    {
        SetIcon(CharSkillIcon->SkillQIcon, CharSkillIcon->SkillEIcon, CharSkillIcon->SkillRIcon);
        //SetTexture(CharSkillIcon->SkillQIcon, CharSkillIcon->SkillEIcon, CharSkillIcon->SkillRIcon);
    }
}

void UYggSkillBarUserWidget::SetIcon(UTexture2D* Q, UTexture2D* E, UTexture2D* R)
{
    if (Skill_Q && Q)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(Q);
        Brush.ImageSize = FVector2D(128.0f, 128.0f);
        Skill_Q->SetBrush(Brush);
    }

    if (Skill_E && E)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(E);
        Brush.ImageSize = FVector2D(128.0f, 128.0f);
        Skill_E->SetBrush(Brush);
    }

    if (Skill_R && R)
    {
        FSlateBrush Brush;
        Brush.SetResourceObject(R);
        Brush.ImageSize = FVector2D(128.0f, 128.0f);
        Skill_R->SetBrush(Brush);
    }
}

void UYggSkillBarUserWidget::SetTexture(UTexture2D* Q, UTexture2D* E, UTexture2D* R)
{
    SkillQ = Q;
    SkillE = E;
    SkillR = R;
    //SkillQ = Q;
}