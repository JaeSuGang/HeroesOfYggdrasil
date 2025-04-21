// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroRevenant.h"


// Input
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"

// Movement
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/YggHeroAnimInstance.h"

// Tag
#include "Attribute/HeroAttributeComponent.h"

// Network
#include "Net/UnrealNetwork.h"

#include "Global/YggProjectileActor.h"
#include "MainGame/UI/MainGameHUD.h"

AYggHeroRevenant::AYggHeroRevenant()
{

}

void AYggHeroRevenant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
		if (ActionMap.Contains(FName("Attack")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Triggered, this, &AYggHeroRevenant::Attack);
		}
		if (ActionMap.Contains(FName("SkillE")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillE")], ETriggerEvent::Triggered, this, &AYggHeroRevenant::SkillE);
		}
		if (ActionMap.Contains(FName("SkillQ")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillQ")], ETriggerEvent::Triggered, this, &AYggHeroRevenant::SkillQ);
		}
	}
}



void AYggHeroRevenant::BeginPlay()
{
	Super::BeginPlay();
	if (HeroAttributeComponent)
	{
		HeroAttributeComponent->ServerSetBaseData_Implementation(TEXT("Revenant"));
	}

}

void AYggHeroRevenant::Attack(const FInputActionValue& Value)
{
	if (bAimMode == false) 
	{
		SetAimMode(true);
	}
	if (!HeroAttributeComponent->HasTagExact(TEXT("Character.State.PressedAttack")))
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.PressedAttack"));
	}
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	FVector CamLoc;
	FRotator CamRot;
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	FVector TraceEnd = CamLoc + CamRot.Vector() * 10000.f;

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CamLoc, TraceEnd, ECC_Visibility, QueryParams);

	FVector TargetLocation = bHit ? HitResult.ImpactPoint : TraceEnd;
	FVector AimDir = (TargetLocation - GetActorLocation()).GetSafeNormal();

	Server_SetPendingAimDirection(AimDir);
	
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastAttackRevenant(Value);
	}
	else
	{
		ServerAttackRevenant(Value);
		return;
	}
}

void AYggHeroRevenant::ServerAttackRevenant_Implementation(const FInputActionValue& Value)
{
	Attack(Value);
}

void AYggHeroRevenant::MulticastAttackRevenant_Implementation(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		return;
	}
	FName MontageName = *FString::Printf(TEXT("Attack"));
	float AttackSpeed = HeroAttributeComponent->AttackSpeedRate;
	HeroAnimInstance->PlayMontage(MontageName, AttackSpeed);
}

void AYggHeroRevenant::SkillQ(const FInputActionValue& Value)
{

	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (bAimMode == false)
	{
		SetAimMode(true);
	}
	//if (HeroAttributeComponent->SkillQCurCoolTime > 0.0f) return;
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastHeroSkillQ(Value);
	}
	else
	{
		ServerHeroSkillQ(Value);
	}

	float CoolTime = HeroAttributeComponent->SkillQMaxCoolTime;
	OnSkillQ.Broadcast(FName("SkillQ"), CoolTime);
}

void AYggHeroRevenant::SkillE(const FInputActionValue& Value)
{
	if (bAimMode == false)
	{
		SetAimMode(true);
	}
	Super::SkillE(Value);
}



void AYggHeroRevenant::Server_SetPendingAimDirection_Implementation(const FVector& InAimDir)
{
	AimDirection = InAimDir;
}
