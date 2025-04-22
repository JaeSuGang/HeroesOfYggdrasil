// Coded By AssortRock Unreal Engine Class Project


#include "Player/YggHeroAurora.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

// Input System Modules
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Animation/YggHeroAnimInstance.h"

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

	if (ActionMap.IsEmpty()) return;
	ActionMap.Remove(FName("ToggleAimMode"));
	ActionMap.Remove(FName("CameraZoomInOut"));

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
		if (ActionMap.Contains(FName("Attack")))
		{
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Triggered, this, &AYggHeroAurora::Attack);
			EnhancedInput->BindAction(ActionMap[TEXT("Attack")], ETriggerEvent::Completed, this, &AYggHeroAurora::EndAttack);
		}
		if (ActionMap.Find(FName("Fly")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Fly")), ETriggerEvent::Triggered, this, &AYggHeroAurora::Fly);
		}
		if (ActionMap.Find(FName("SkillQ")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillQ")), ETriggerEvent::Triggered, this, &AYggHeroAurora::SkillQ);
		}
		if (ActionMap.Find(FName("SkillE")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillE")), ETriggerEvent::Triggered, this, &AYggHeroAurora::SkillE);
		}
		if (ActionMap.Find(FName("SkillR")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillR")), ETriggerEvent::Triggered, this, &AYggHeroAurora::SkillR);
		}
		if (ActionMap.Find(FName("Roll")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Roll")), ETriggerEvent::Triggered, this, &AYggHeroAurora::Roll);
		}
	}
}

void AYggHeroAurora::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FTimerHandle InitTimer;
	GetWorld()->GetTimerManager().SetTimer(InitTimer, [this]()
	{
		SetAimMode(true);
	}, 2.0f, false);
}

void AYggHeroAurora::Attack(const FInputActionValue& Value)
{
	if (bIsSkillE)
	{
		bIsSkillE = false;

		OnSkillCastEnd.Broadcast();
		return;
	}

	Super::Attack(Value);
}

void AYggHeroAurora::EndAttack(const FInputActionValue& Value)
{
	HeroAttributeComponent->RemoveTag(TEXT("Character.State.PressedAttack"));
}

void AYggHeroAurora::Fly(const FInputActionValue& Value)
{
	// GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, FString("dddd"));
}

void AYggHeroAurora::SkillQ(const FInputActionValue& Value)
{
	Super::SkillQ(Value);

	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));
	HeroAttributeComponent->AddTag(TEXT("Character.State.NotRollable"));

	float ContinueTime = HeroAttributeComponent->SkillQMaxContinueTime;
	FTimerHandle TimeHandle;
	GetWorld()->GetTimerManager().SetTimer(TimeHandle, [this]()
	{
		if (USkeletalMeshComponent* MeshComp = GetMesh())
		{
			if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
			{
				UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
				if (CurrentMontage)
				{
					float BlendOutTime = 0.25f;
					AnimInstance->Montage_Stop(BlendOutTime, CurrentMontage);
				}
			}
		}

		HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));
		HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotAttackable"));

	}, ContinueTime + 0.8f, false);
}

void AYggHeroAurora::SkillE(const FInputActionValue& Value)
{
	Super::SkillE(Value);

	bIsSkillE = true;

	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));
}

void AYggHeroAurora::SkillR(const FInputActionValue& Value)
{
	Super::SkillR(Value);

	HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotMoveable"));
}

void AYggHeroAurora::Roll(const FInputActionValue& Value)
{
	Super::Roll(Value);


}
