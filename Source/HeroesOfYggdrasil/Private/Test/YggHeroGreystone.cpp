// Coded By AssortRock Unreal Engine Class Project

#include "Test/YggHeroGreystone.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AYggHeroGreystone::AYggHeroGreystone()
{
}

AYggHeroGreystone::~AYggHeroGreystone()
{
}

void AYggHeroGreystone::BeginPlay()
{
	Super::BeginPlay();
}

void AYggHeroGreystone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AYggHeroGreystone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		if (ActionMap.Find(FName("Move")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Move")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Move);
			UE_LOG(LogTemp, Warning, TEXT("MoveAction Bind Succesed"));
		}
		if (ActionMap.Find(FName("Look")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Look")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Look);
			UE_LOG(LogTemp, Warning, TEXT("LookAction Bind Succesed"));
		}
		if (ActionMap.Find(FName("Jump")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Jump")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Jump);
			UE_LOG(LogTemp, Warning, TEXT("JumpAction Bind Succesed"));
		}
		if (ActionMap.Find(FName("Attack")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("Attack")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::Attack);
			UE_LOG(LogTemp, Warning, TEXT("AttackAction Bind Succesed"));
		}
		if (ActionMap.Find(FName("SkillQ")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillQ")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::SkillQ);
			UE_LOG(LogTemp, Warning, TEXT("AttackAction Bind Succesed"));
		}
		if (ActionMap.Find(FName("SkillE")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillE")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::SkillE);
			UE_LOG(LogTemp, Warning, TEXT("AttackAction Bind Succesed"));
		}
		if (ActionMap.Find(FName("SkillR")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("SkillR")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::SkillR);
			UE_LOG(LogTemp, Warning, TEXT("AttackAction Bind Succesed"));
		}
		if (ActionMap.Find(FName("ToggleAimMode")))
		{
			EnhancedInput->BindAction(*ActionMap.Find(FName("ToggleAimMode")), ETriggerEvent::Triggered, this, &AYggHeroGreystone::ToggleAimMode);
		}
	}
}

void AYggHeroGreystone::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void AYggHeroGreystone::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
}

void AYggHeroGreystone::Attack(const FInputActionValue& Value)
{
	Super::Attack(Value);
}

void AYggHeroGreystone::SkillQ(const FInputActionValue& Value)
{
	Super::SkillQ(Value);

	UE_LOG(LogTemp, Warning, TEXT("SkiilQ"));
}

void AYggHeroGreystone::SkillE(const FInputActionValue& Value)
{
	Super::SkillE(Value);
}

void AYggHeroGreystone::SkillR(const FInputActionValue& Value)
{
	Super::SkillR(Value);
}
