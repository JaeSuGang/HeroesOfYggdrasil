// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroKhaimera.h"

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



#include "Component/SceneComponent/YggAttackCapsuleComponent.h"
#include "Component/SceneComponent/YggParticleSystemComponent.h"


AYggHeroKhaimera::AYggHeroKhaimera()
{
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("LeftAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh(), TEXT("weapon_l"));
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("LeftAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("RightAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh(), TEXT("weapon_r"));
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("RightAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillQAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillQAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillEAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillEAttack"), AttackCapsuleComponent);
	}
	{
		UYggAttackCapsuleComponent* AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillRAttack"));
		AttackCapsuleComponent->SetupAttachment(GetMesh());
		AttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillRAttack"), AttackCapsuleComponent);
	}
}

void AYggHeroKhaimera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
	}
}

void AYggHeroKhaimera::BeginPlay()
{
	Super::BeginPlay();
	if (HeroAttributeComponent)
	{
		HeroAttributeComponent->ServerSetBaseData_Implementation(TEXT("Khaimera"));

	}
	
	if (HasAuthority())
	{
		/*UpdateStatus();*/
	}
}

void AYggHeroKhaimera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}






void AYggHeroKhaimera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


