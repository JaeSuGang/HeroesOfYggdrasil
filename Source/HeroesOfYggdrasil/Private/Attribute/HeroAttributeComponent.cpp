// Coded By AssortRock Unreal Engine Class Project


#include "Attribute/HeroAttributeComponent.h"
#include "Engine/DataTable.h"
#include "Net/UnrealNetwork.h"

void UHeroAttributeComponent::BeginPlay()
{
    Super::BeginPlay();

    ClientDelegate_OnComboChanged.AddDynamic(this, &UHeroAttributeComponent::SaveComboAttack);
    ClientDelegate_OnComboChanged.AddDynamic(this, &UHeroAttributeComponent::ResetComboAttack);
}

void UHeroAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UHeroAttributeComponent, CurComboAttack);
}

void UHeroAttributeComponent::SaveComboAttack()
{
    //if (GetOwner()->HasAuthority())
    //{
    //    Server_SaveComboAttack();
    //}
    //else
    //{
    //    // 서버에게 실행 요청 (클라이언트가 직접 증가시키지 않음)
    //    Server_SaveComboAttack();
    //}
}

void UHeroAttributeComponent::ResetComboAttack()
{
    CurComboAttack = 0;
}
//
//void UHeroAttributeComponent::Server_SaveComboAttack_Implementation()
//{
//    CurComboAttack++;
//       
//    OnRep_Combo();    
//}
//
//bool UHeroAttributeComponent::Server_SaveComboAttack_Validate()
//{
//    return true;
//}
//
//void UHeroAttributeComponent::Server_ResetComboAttack_Implementation()
//{
//}

void UHeroAttributeComponent::OnRep_Combo()
{
    if (GetOwner()->HasAuthority())
        ServerDelegate_OnComboChanged.Broadcast();

    if (GetOwner()->HasLocalNetOwner())
        ClientDelegate_OnComboChanged.Broadcast();
    
    MulticastDelegate_OnComboChanged.Broadcast();
}