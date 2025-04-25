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
	AttackCapsuleComponentMap.Reset();
	{
		NormalAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("NormalAttack"));
		NormalAttackCapsuleComponent->SetupAttachment(GetMesh());
		NormalAttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("NormalAttack"), NormalAttackCapsuleComponent);
	}
	
	{
		SkillQAttackAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillQAttack"));
		SkillQAttackAttackCapsuleComponent->SetupAttachment(GetMesh());
		SkillQAttackAttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillQAttack"), SkillQAttackAttackCapsuleComponent);
	}
	{
		SkillEAttackAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillEAttack"));
		SkillEAttackAttackCapsuleComponent->SetupAttachment(GetMesh());
		SkillEAttackAttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillEAttack"), SkillEAttackAttackCapsuleComponent);
	}
	{
		SkillRAttackAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("SkillRAttack"));
		SkillRAttackAttackCapsuleComponent->SetupAttachment(GetMesh());
		SkillRAttackAttackCapsuleComponent->SetOwnerCharacter(this);
		AttackCapsuleComponentMap.Add(TEXT("SkillRAttack"), SkillRAttackAttackCapsuleComponent);
	}
}

void AYggHeroKhaimera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
		if (ActionMap.Contains(FName("SkillQ")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("SkillQ")], ETriggerEvent::Triggered, this, &AYggHeroKhaimera::SkillQ);
		}
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
void AYggHeroKhaimera::SkillQ(const FInputActionValue& Value)
{
	if (HeroAttributeComponent->HasTagExact(TEXT("Character.State.NotAttackable")))
	{
		return;
	}
	if (HeroAttributeComponent->SkillQCurCoolTime > 0.0f) return;
	if (HasAuthority())
	{
		HeroAttributeComponent->AddTag(TEXT("Character.State.NotAttackable"));
		MulticastHeroSkillQ(Value);
	}
	else
	{
		ServerHeroSkillQ(Value);
	}

	float CoolTime = HeroAttributeComponent->SkillQMaxCoolTime * (1 - HeroAttributeComponent->CooldownReduction);
	OnSkillQ.Broadcast(FName("SkillQ"), CoolTime);
}





void AYggHeroKhaimera::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


