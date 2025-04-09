// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggSkillBarUserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

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
            FString FullClassName = Pawn->GetClass()->GetName();

            FString CleanName;
            FullClassName.Split(TEXT("_C"), &CleanName, nullptr);

            FString HeroName;
            CleanName.Split(TEXT("BP_YggHero"), nullptr, &HeroName);

            SetSkillIcon(FName(HeroName));

            InitSkills();

            AYggHero* Hero = Cast<AYggHero>(Pawn);
            if (!IsValid(Hero) || !Hero->IsLocallyControlled()) return;

            Hero->OnSkillQ.RemoveDynamic(this, &UYggSkillBarUserWidget::StartCoolTime);
            Hero->OnSkillE.RemoveDynamic(this, &UYggSkillBarUserWidget::StartCoolTime);
            Hero->OnSkillR.RemoveDynamic(this, &UYggSkillBarUserWidget::StartCoolTime);

            Hero->OnSkillQ.AddDynamic(this, &UYggSkillBarUserWidget::StartCoolTime);
            Hero->OnSkillE.AddDynamic(this, &UYggSkillBarUserWidget::StartCoolTime);
            Hero->OnSkillR.AddDynamic(this, &UYggSkillBarUserWidget::StartCoolTime);
        }
    }


    //StartCoolTime(FName("Q"), 5.0f);
    //StartCoolTime(FName("E"), 3.0f);
    //StartCoolTime(FName("R"), 10.0f);
}

void UYggSkillBarUserWidget::InitSkills()
{
    FVector2D IconSize(128.0f, 128.0f);

    FSkillData Q;
    Q.Bar = Skill_Q;
    Q.Icon = QTexture;
    Q.Text = CoolTimeQ;
    Q.Text->SetVisibility(ESlateVisibility::Hidden);
    SetupSkillBar(Q.Bar, Q.Icon, IconSize);
    SkillMap.Add("SkillQ", Q);

    FSkillData E;
    E.Bar = Skill_E;
    E.Icon = ETexture;
    E.Text = CoolTimeE;
    E.Text->SetVisibility(ESlateVisibility::Hidden);
    SetupSkillBar(E.Bar, E.Icon, IconSize);
    SkillMap.Add("SkillE", E);

    FSkillData R;
    R.Bar = Skill_R;
    R.Icon = RTexture;
    R.Text = CoolTimeR;
    R.Text->SetVisibility(ESlateVisibility::Hidden);
    SetupSkillBar(R.Bar, R.Icon, IconSize);
    SkillMap.Add("SkillR", R);

}

FSlateBrush MakeBrush(UTexture2D* Tex, FVector2D Size, float Brightness = 1.0f)
{
    FSlateBrush Brush;
    Brush.SetResourceObject(Tex);
    Brush.ImageSize = Size;
    Brush.TintColor = FLinearColor(Brightness, Brightness, Brightness, 1.0f);
    Brush.DrawAs = ESlateBrushDrawType::Image;
    return Brush;
}

void UYggSkillBarUserWidget::SetupSkillBar(UProgressBar* Bar, UTexture2D* Tex, FVector2D Size)
{
    if (!Bar || !Tex) return;

    FProgressBarStyle Style;
    Style.BackgroundImage = MakeBrush(Tex, Size, 1.0f);
    Style.FillImage = MakeBrush(Tex, Size, 0.3f);
    Bar->SetWidgetStyle(Style);

    Bar->SetPercent(0.0f);
}


void UYggSkillBarUserWidget::SetSkillIcon(FName Character)
{
    if (!SkillIcons) return;

    CharSkillIcon = SkillIcons->FindRow<FSkillIcon>(Character, nullptr);

    if (CharSkillIcon)
    {
        SetTexture(CharSkillIcon->SkillQIcon, CharSkillIcon->SkillEIcon, CharSkillIcon->SkillRIcon);
    }
}

void UYggSkillBarUserWidget::SetTexture(UTexture2D* Q, UTexture2D* E, UTexture2D* R)
{
    QTexture = Q;
    ETexture = E;
    RTexture = R;
}

void UYggSkillBarUserWidget::StartCoolTime(FName Key, float Duration)
{
    if (!SkillMap.Contains(Key)) return;

    FSkillData& Skill = SkillMap[Key];
    Skill.CoolTime = Duration;
    Skill.RemainingTime = Duration;
    Skill.Text->SetText(FText::AsNumber(FMath::FloorToInt(Skill.RemainingTime)));
    Skill.Text->SetVisibility(ESlateVisibility::Visible);

    if (Skill.Bar)
    {
        Skill.Bar->SetPercent(1.0f);
    }

    GetWorld()->GetTimerManager().SetTimer(Skill.TimerHandle, FTimerDelegate::CreateUObject(this, &UYggSkillBarUserWidget::UpdateCoolTime, Key), 0.05f, true);
}

void UYggSkillBarUserWidget::UpdateCoolTime(FName Key)
{
    if (!SkillMap.Contains(Key)) return;

    FSkillData& Skill = SkillMap[Key];
    Skill.RemainingTime -= 0.05f;
    Skill.Text->SetText(FText::AsNumber(FMath::FloorToInt(Skill.RemainingTime)));

    if (Skill.RemainingTime <= 0.0f)
    {
        EndCoolTime(Key);
        return;
    }

    float Ratio = Skill.RemainingTime / Skill.CoolTime;

    if (IsValid(Skill.Bar))
    {
        Skill.Bar->SetPercent(Ratio);
    }
}

void UYggSkillBarUserWidget::EndCoolTime(FName Key)
{
    if (!SkillMap.Contains(Key)) return;

    FSkillData& Skill = SkillMap[Key];
    Skill.Text->SetVisibility(ESlateVisibility::Hidden);
    GetWorld()->GetTimerManager().ClearTimer(Skill.TimerHandle);

    if (IsValid(Skill.Bar))
    {
        Skill.Bar->SetPercent(0.0f);
    }
}

