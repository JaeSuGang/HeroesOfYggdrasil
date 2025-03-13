// Coded By AssortRock Unreal Engine Class Project

#include "MainGame/PlayerSelectZone.h"

#include "EngineUtils.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Core/YggPlayerState.h"
#include "Data/Playables.h"
#include "MainGame/StageManager.h"
#include "Core/YggPlayerController.h"
#include "Player/YggHero.h"

APlayerSelectZone::APlayerSelectZone()
{
	SetReplicateMovement(true);
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	bAlwaysRelevant = true;
	bReplicates = true;
	CurrentTableIndex = 0;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComponent->bHiddenInGame = true;
	RootComponent = StaticMeshComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 1000.0f;
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
}

void APlayerSelectZone::Restart()
{
	Super::Restart();

	if (AYggPlayerController* YPC = Cast<AYggPlayerController>(GetController()))
	{
		if (HasAuthority())
		{
			if (APlayerState* PS = GetPlayerState())
			{
				int nPlayerId = PS->GetPlayerId();
				SetToPosition(nPlayerId);
			}
			else
			{
				SetToPosition(0);
			}

			AddActorLocalRotation(FRotator{ 0, 180, 0 });
			SpawnSelectable(0);
		}
	}
}

void APlayerSelectZone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerSelectZone::PossessedBy(AController* controller)
{
	Super::PossessedBy(controller);

	
}

void APlayerSelectZone::EndPlay(EEndPlayReason::Type endReason)
{
	Super::EndPlay(endReason);
}

void APlayerSelectZone::BeginPlay()
{
	Super::BeginPlay();

	TActorIterator<APlayerStart> Iter(GetWorld());
	PlayerStart = *Iter;
}

void APlayerSelectZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerSelectZone, CurrentTableIndex);
}

APawn* APlayerSelectZone::GetSpawnedSelectable() const
{
	return SpawnedSelectable;
}

void APlayerSelectZone::SetToPosition_Implementation(int nIndex)
{
	TActorIterator<APlayerStart> Iter(GetWorld());
	PlayerStart = *Iter;

	FVector location = PlayerStart->GetActorLocation();
	location = location + CameraDistance;
	location = location + ZoneInterval * ((float)nIndex - 1.5f);
	SetActorLocation(location);
}

void APlayerSelectZone::SpawnSelectable_Implementation(int nSpawnableIndex)
{
	if (SpawnedSelectable)
		SpawnedSelectable->Destroy();

	TArray<FPlayableCharacterRow*> Rows;
	SelectablesTable->GetAllRows(TEXT("GetAllRows"), Rows);
	CurrentTableIndex = nSpawnableIndex % Rows.Num();
	if (CurrentTableIndex < 0)
		CurrentTableIndex = Rows.Num() + CurrentTableIndex;

	FActorSpawnParameters SpawnParams{};
	SpawnParams.Owner = nullptr;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnedSelectable = GetWorld()->SpawnActor<APawn>(Rows[CurrentTableIndex]->PlayPawn, GetActorLocation(), GetActorRotation(), SpawnParams);

}

void APlayerSelectZone::SelectCharacter_Implementation()
{
	if (HasAuthority())
	{
		AYggPlayerController* YPC = this->GetController<AYggPlayerController>();
		if (!YPC || !SpawnedSelectable)
		{
			return;
		}

		FVector CameraLocation = FVector::ZeroVector;
		FRotator CameraRotation = FRotator::ZeroRotator;
		float CameraArmLength = 0.0f;
		FVector CameraSocketOffset = FVector::ZeroVector;

		// FixedPawn 카메라 위치 저장.
		if (APawn* FixedPawn = YPC->GetPawn())
		{
			if (USpringArmComponent* FixedSpringArm = FixedPawn->FindComponentByClass<USpringArmComponent>())
			{
				CameraLocation = FixedSpringArm->GetComponentLocation();
				CameraRotation = FixedSpringArm->GetComponentRotation();
				CameraArmLength = FixedSpringArm->TargetArmLength;
				CameraSocketOffset = FixedSpringArm->SocketOffset;
			}
		}

		YPC->SetViewTarget(this);
		YPC->UnPossess();
		YPC->Possess(SpawnedSelectable);

		// 새 Hero에 FixedPawn 카메라 정보 보내기.
		if (AYggHero* NewHero = Cast<AYggHero>(SpawnedSelectable))
		{
			if (USpringArmComponent* NewSpringArm = NewHero->FindComponentByClass<USpringArmComponent>())
			{
				NewSpringArm->TargetArmLength = CameraArmLength;
				NewSpringArm->SocketOffset = CameraSocketOffset;
				NewSpringArm->SetWorldLocationAndRotation(CameraLocation, CameraRotation);
			}

			YPC->SetControlRotation(CameraRotation);
			NewHero->SetCamera(CameraLocation, CameraRotation, CameraArmLength, CameraSocketOffset);
		}

		SpawnedSelectable = nullptr;
		this->Destroy();
	}
}



void APlayerSelectZone::SpawnNextSelectable(int nHowMuchNext)
{
	CurrentTableIndex += nHowMuchNext;

	SpawnSelectable(CurrentTableIndex);
}
