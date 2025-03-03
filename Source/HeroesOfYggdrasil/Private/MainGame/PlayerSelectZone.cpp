// Coded By AssortRock Unreal Engine Class Project

#include "MainGame/PlayerSelectZone.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Data/Playables.h"
#include "MainGame/StageManager.h"
#include "Core/YggPlayerController.h"

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

void APlayerSelectZone::EndPlay(EEndPlayReason::Type endReason)
{
	Super::EndPlay(endReason);
}

void APlayerSelectZone::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SortPosition();
		SpawnSelectable(0);
	}
}

void APlayerSelectZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerSelectZone, CurrentTableIndex);
}

void APlayerSelectZone::SortPosition_Implementation()
{
	TArray<AActor*> Zones;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerSelectZone::StaticClass(), Zones);

	int32 ZoneCount = Zones.Num();
	for (int i = 0; i < ZoneCount; ++i)
	{
		FVector PosOffset = LocationOffset * (i - (ZoneCount - 1) * 0.5f);
		FTransform LoopTransform = SpawnTransform;
		LoopTransform.SetLocation(LoopTransform.GetLocation() + PosOffset);
		APlayerSelectZone* CastedZone = Cast<APlayerSelectZone>(Zones[i]);
		CastedZone->SetActorTransform(LoopTransform);
		if (CastedZone->SpawnedSelectable)
			CastedZone->SpawnedSelectable->SetActorTransform(LoopTransform);
	}
}

void APlayerSelectZone::SpawnSelectable_Implementation(int nSpawnableIndex)
{
	if (SpawnedSelectable)
		SpawnedSelectable->Destroy();

	TArray<FPlayableCharacterRow*> Rows;
	SelectablesTable->GetAllRows(TEXT("GetAllRows"), Rows);
	CurrentTableIndex = nSpawnableIndex % Rows.Num();

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
		YPC->UnPossess();
		YPC->Possess(SpawnedSelectable);
		SpawnedSelectable = nullptr;
		this->Destroy();
	}
}

void APlayerSelectZone::SpawnNextSelectable_Implementation()
{
	CurrentTableIndex++;

	SpawnSelectable(CurrentTableIndex);
}
