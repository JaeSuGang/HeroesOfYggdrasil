// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroAurora.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

// Input System Modules
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AYggHeroAurora::AYggHeroAurora()
{
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

void AYggHeroAurora::BeginPlay()
{
	Super::BeginPlay();


	if (!HeroAttributeComponent) return;
	HeroAttributeComponent->ServerSetBaseData_Implementation(TEXT("Aurora"));
	//UpdateStatus();	
}

void AYggHeroAurora::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYggHeroAurora::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInput)
	{
		if (ActionMap.Find(FName("Fly")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Fly")), ETriggerEvent::Triggered, this, &AYggHeroAurora::Fly);
		}
	}
}

void AYggHeroAurora::Fly(const FInputActionValue& Value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString("dddd"));
}
