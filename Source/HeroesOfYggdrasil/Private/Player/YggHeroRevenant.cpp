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
#include "Global/YggBombActor.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Kismet/GameplayStatics.h"

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

void AYggHeroRevenant::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AYggHeroRevenant, AimDirection);
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
	FVector NewAimDir = Local_GetAimDirection(LeftSocketName);
	Server_SetAimDirection(NewAimDir);
	Super::Attack(Value);
}




void AYggHeroRevenant::SkillQ(const FInputActionValue& Value)
{
	if (bAimMode == false)
	{
		SetAimMode(true);
	}
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	FVector NewAimDir = Local_GetAimDirection(LeftSocketName);
	Server_SetAimDirection(NewAimDir);
	HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
	if (HasAuthority())
	{
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
	FVector NewAimDir = Local_GetAimDirection(RightSocketName);
	Server_SetAimDirection(NewAimDir);
	Super::SkillE(Value);
}



FVector AYggHeroRevenant::Local_GetAimDirection(FName _SocketName)
{
	// 1. 카메라 위치 · 회전
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return FVector::ZeroVector;

	FVector CamLoc;
	FRotator CamRot;
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	// 2. 1차 라인트레이스 : 카메라 → 조준 지점
	const float TraceRange = 10000.f;
	FVector TraceEnd = CamLoc + CamRot.Vector() * TraceRange;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(
		Hit, CamLoc, TraceEnd, ECC_Visibility, Params);

	const FVector TargetLoc = Hit.bBlockingHit ? Hit.ImpactPoint : TraceEnd;

	// 3. 총구 위치
	const FVector MuzzleLoc = GetMesh()->GetSocketLocation(_SocketName);

	// 4. 정확한 발사 방향 = (목표 - 총구). 정규화
	FVector AimDir = (TargetLoc - MuzzleLoc).GetSafeNormal();

	return AimDir;
}



void AYggHeroRevenant::Server_SetAimDirection_Implementation(const FVector& InAimDir)
{
	AimDirection = InAimDir;
}
