// Coded By AssortRock Unreal Engine Class Project

// UI
#include "MainGame/UI/YggHPBarUserWidget.h"
#include "Components/ProgressBar.h"

// Player
#include "Player/YggHero.h"
#include "Core/YggCharacter.h"

// Attribute
#include "Attribute/HeroAttributeComponent.h"

// Data
#include "Engine/DataTable.h"
#include "Data/YggStructData.h"

void UYggHPBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

    APlayerController* PC = GetOwningPlayer();
    if (PC)
    {
        AYggHero* Player = Cast<AYggHero>(PC->GetPawn());
        if (Player)
        {
            // 플레이어 캐릭터에서 UHeroAttributeComponent 가져오기
            UHeroAttributeComponent* HeroAttributeComp = Player->GetHeroAttributeComponent();
            if (HeroAttributeComp)
            {
                // 캐릭터의 이름을 가져와서 키 값으로 사용
                FName HeroName = Player->GetFName();

                // HeroName을 사용하여 데이터 테이블에서 검색
                FHeroBaseStatusInfoRow* Row = HeroAttributeComp->Data->FindRow<FHeroBaseStatusInfoRow>(HeroName, TEXT("Context"));
                if (Row)
                {
                    CurHP = Row->CurHP;
                    MaxHP = Row->MaxHP;

                    float SkillRCoolTime = Row->SkillRInfo.CoolTime;
                }
            }
        }
    }


    UpdateHPBar(CurHP, MaxHP);
}

void UYggHPBarUserWidget::UpdateHPBar(float CurrentHP, float MaximumHP)
{
	if (HPBar)
	{
		HPBar->SetPercent(CurrentHP / MaximumHP);
	}
}
