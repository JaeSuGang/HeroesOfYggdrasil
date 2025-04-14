// Coded By AssortRock Unreal Engine Class Project

#include "MainGame/PlayerSelectZone.h"

#include "EngineUtils.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerStart.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#include "StageSystem/StageSystem.h"
#include "Core/YggPlayerState.h"
#include "Data/Playables.h"
#include "StageSystem/StageManager.h"
#include "Core/YggPlayerController.h"
#include "Player/YggHero.h"
#include "MainGame/UI/MainGameHUD.h"

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

	if (UStageSystem* StageSystem = UStageSystem::Get(this))
	{
		StageSystem->OnGameStarted.AddDynamic(this, &APlayerSelectZone::OnStartGame);
	}
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

void APlayerSelectZone::ForceMainWidget_Implementation()
{
	if (AMainGameHUD* MGH = GetWorld()->GetFirstPlayerController()->GetHUD<AMainGameHUD>())
	{
		MGH->CloseCurrentWidget();
		MGH->ShowMainGameWidget();
	}
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
	SpawnedSelectable->SetPlayerState(GetPlayerState());
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
		YPC->UnPossess();
		YPC->Possess(SpawnedSelectable);
		YPC->SetViewTarget(this);
	
		YPC->SetViewTargetWithBlend(SpawnedSelectable, 2.0f, EViewTargetBlendFunction::VTBlend_Cubic, true);
		YPC->SetInputEnabled(false);
		FTimerHandle BlendTimerHandle;
		GetWorldTimerManager().SetTimer(BlendTimerHandle, 
			[this,YPC]() 
			{
				YPC->SetInputEnabled(true); 
				SpawnedSelectable = nullptr;
				this->Destroy();
			}, 2.0f, false);
	}
}

void APlayerSelectZone::SpawnNextSelectable(int nHowMuchNext)
{
	CurrentTableIndex += nHowMuchNext;

	SpawnSelectable(CurrentTableIndex);
}

void APlayerSelectZone::OnStartGame(FOnGameStartParams OnGameStartParams)
{
	if (HasAuthority())
	{
		SelectCharacter();
		ForceMainWidget();
	}
}
