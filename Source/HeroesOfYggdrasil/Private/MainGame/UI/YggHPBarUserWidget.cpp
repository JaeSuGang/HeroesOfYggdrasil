// Coded By AssortRock Unreal Engine Class Project

// UI
#include "MainGame/UI/YggHPBarUserWidget.h"
#include "Components/ProgressBar.h"

// Player
#include "Player/YggHero.h"
#include "Core/YggCharacter.h"

// Attribute
#include "Attribute/CharacterAttributeComponent.h"

// Data
#include "Engine/DataTable.h"
#include "Data/YggStructData.h"

void UYggHPBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

    APlayerController* PC = GetOwningPlayer();
    
    UCharacterAttributeComponent* CAC = PC->GetPawn()->GetComponentByClass<UCharacterAttributeComponent>();
    
    if (CAC)
    {
        CAC->ClientDelegate_OnHealthChanged.AddDynamic(this, &UYggHPBarUserWidget::UpdateHPBar);
    }
}

void UYggHPBarUserWidget::UpdateHPBar()
{
    APlayerController* PC = GetOwningPlayer();

    UCharacterAttributeComponent* CAC = PC->GetPawn()->GetComponentByClass<UCharacterAttributeComponent>();

    if (CAC)
    {
        if (HPBar)
    	{
		    HPBar->SetPercent(CAC->GetHp() / CAC->GetMaxHp());
    	}
    }
}

void UYggHPBarUserWidget::UIUpdate()
{
    //APlayerController* PC = GetOwningPlayer();
    //if (PC)
    //{
    //    AYggHero* Player = Cast<AYggHero>(PC->GetPawn());
    //    if (Player)
    //    {
    //        // 플레이어 캐릭터에서 UHeroAttributeComponent 가져오기
    //        UHeroAttributeComponent* HeroAttributeComp = Player->GetHeroAttributeComponent();
    //        if (HeroAttributeComp)
    //        {
    //            FString FullName = Player->GetName(); // "BP_YggHeroGreystone_C_0"

    //            // 앞쪽 "BP_" 제거
    //            FullName.RemoveFromStart(TEXT("BP_"));

    //            // 뒤쪽 "_C" 이후 제거
    //            int32 UnderscoreIndex;
    //            if (FullName.FindChar(TEXT('_'), UnderscoreIndex))
    //            {
    //                FullName = FullName.Left(UnderscoreIndex); // "YggHeroGreystone"
    //            }

    //            // "Hero" 다음 부분만 추출
    //            FString HeroName = FullName.RightChop(FullName.Find(TEXT("Hero")) + 4);

    //            // FName으로 변환
    //            FName FinalHeroName(*HeroName);

    //            // HeroName을 사용하여 데이터 테이블에서 검색
    //            FHeroBaseStatusInfoRow* Row = HeroAttributeComp->Data->FindRow<FHeroBaseStatusInfoRow>(FinalHeroName, TEXT("Context"));
    //            if (Row)
    //            {
    //                CurHP = Row->CurHP;
    //                MaxHP = Row->MaxHP;

    //                float SkillRCoolTime = Row->SkillRInfo.CoolTime;
    //            }
    //        }
    //    }
    //}

    //UpdateHPBar(CurHP, MaxHP);    
}