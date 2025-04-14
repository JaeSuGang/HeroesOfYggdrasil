// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggSkillBarUserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

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
}

void UYggSkillBarUserWidget::InitSkills()
{
    FVector2D IconSize(64.0f, 64.0f);

    FSkillData Q;
    Q.Bar = Skill_Q;
    Q.Image = Skill_Q_Image;
    Q.Icon = QTexture;
    Q.BackGround = BackGroundTexture;
    Q.Text = CoolTimeQ;
    Q.Text->SetVisibility(ESlateVisibility::Hidden);
    SetupSkillBar(Q.Bar, Q.Image, Q.Icon, Q.BackGround, IconSize);
    SkillMap.Add("SkillQ", Q);

    FSkillData E;
    E.Bar = Skill_E;
    E.Image = Skill_E_Image;
    E.Icon = ETexture;
    E.BackGround = BackGroundTexture;
    E.Text = CoolTimeE;
    E.Text->SetVisibility(ESlateVisibility::Hidden);
    SetupSkillBar(E.Bar, E.Image, E.Icon, E.BackGround, IconSize);
    SkillMap.Add("SkillE", E);

    FSkillData R;
    R.Bar = Skill_R;
    R.Image = Skill_R_Image;
    R.Icon = RTexture;
    R.BackGround = BackGroundTexture;
    R.Text = CoolTimeR;
    R.Text->SetVisibility(ESlateVisibility::Hidden);
    SetupSkillBar(R.Bar, R.Image, R.Icon, R.BackGround, IconSize);
    SkillMap.Add("SkillR", R);

    FSkillData Shift;
    Shift.Bar = Skill_Shift;
    Shift.Image = Skill_Shift_Image;
    Shift.Icon = ShiftTexture;
    Shift.BackGround = BackGroundTexture;
    Shift.Text = CoolTimeShift;
    Shift.Text->SetVisibility(ESlateVisibility::Hidden);
    SetupSkillBar(Shift.Bar, Shift.Image, Shift.Icon, Shift.BackGround, IconSize);
    SkillMap.Add("SkillShift", Shift);
}

FSlateBrush MakeBrush(UMaterialInterface* Mat, FVector2D Size, float Brightness = 1.0f)
{
    FSlateBrush Brush;
    Brush.SetResourceObject(Mat);
    Brush.ImageSize = Size;
    Brush.TintColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
    Brush.DrawAs = ESlateBrushDrawType::Image;
    return Brush;
}

void UYggSkillBarUserWidget::SetupSkillBar(UProgressBar* Bar, UImage* Image, UTexture2D* Tex, UTexture2D* BackTex, FVector2D Size)
{
    if (!Bar || !Image || !Tex || !BackTex) return;

    UMaterialInstanceDynamic* ProgressDynMat = UMaterialInstanceDynamic::Create(DiamondMaskMaterial, this);
    ProgressDynMat->SetTextureParameterValue("RenderTarget", BackTex);
    ProgressDynMat->SetTextureParameterValue("DiamondMaskTexture", DiamondMaskTexture);
    ProgressDynMat->SetScalarParameterValue("Progress", 1.0f);
    //ProgressDynMat->SetVectorParameterValue("TintColor", FLinearColor::White);

    FProgressBarStyle PStyle;
    PStyle.BackgroundImage = MakeBrush(ProgressDynMat, Size, 1.0f);
    PStyle.FillImage = MakeBrush(ProgressDynMat, Size, 1.0f);
    Bar->SetWidgetStyle(PStyle);
    Bar->SetPercent(1.0f);

    Bar->WidgetStyle.FillImage.TintColor = FLinearColor::White;
    MaterialMap.Add(Bar, ProgressDynMat);

    UMaterialInstanceDynamic* ImageDynMat = UMaterialInstanceDynamic::Create(MaskedMaterial, this);
    ImageDynMat->SetTextureParameterValue("RenderTarget", Tex);
    ImageDynMat->SetTextureParameterValue("DiamondmaskTexture", DiamondMaskTexture);

    Image->SetBrush(MakeBrush(ImageDynMat, Size, 1.0f));
}


void UYggSkillBarUserWidget::SetSkillIcon(FName Character)
{
    if (!SkillIcons) return;

    CharSkillIcon = SkillIcons->FindRow<FSkillIcon>(Character, nullptr);

    if (CharSkillIcon)
    {
        SetTexture(CharSkillIcon->SkillQIcon, CharSkillIcon->SkillEIcon, CharSkillIcon->SkillRIcon, CharSkillIcon->SkillShifteIcon, CharSkillIcon->SkillBackGroundIcon);
    }
}

void UYggSkillBarUserWidget::SetTexture(UTexture2D* Q, UTexture2D* E, UTexture2D* R, UTexture2D* Shift, UTexture2D* BackGround)
{
    QTexture = Q;
    ETexture = E;
    RTexture = R;
    ShiftTexture = Shift;
    BackGroundTexture = BackGround;
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
        Skill.Bar->SetPercent(1.0f);
        if (UMaterialInstanceDynamic** MatPtr = MaterialMap.Find(Skill.Bar))
        {
            (*MatPtr)->SetScalarParameterValue("Progress", 1.0f - Ratio);
        }
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
        Skill.Bar->SetPercent(1.0f);
        if (UMaterialInstanceDynamic** MatPtr = MaterialMap.Find(Skill.Bar))
        {
            (*MatPtr)->SetScalarParameterValue("Progress", 1.0f);
        }
    }
}

