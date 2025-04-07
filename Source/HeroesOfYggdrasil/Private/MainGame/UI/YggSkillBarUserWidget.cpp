// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggSkillBarUserWidget.h"

#include "Components/Image.h"


void UYggSkillBarUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
}

void UYggSkillBarUserWidget::NativeConstruct()
{
    Super::NativeConstruct();


}

void UYggSkillBarUserWidget::SetSkillIcon(FName Character)
{
    if (!SkillIcons) return;

    CharSkillIcon = SkillIcons->FindRow<FSkillIcon>(Character, nullptr);

    if (CharSkillIcon)
    {
        SetIcon(CharSkillIcon->SkillQIcon, CharSkillIcon->SkillEIcon, CharSkillIcon->SkillRIcon);
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

