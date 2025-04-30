// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMiniMapIconActor.h"
#include "MainGame/UI/YggUIDataAsset.h"
#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/UI/YggMiniMapManager.h"
#include "Core/YggGameInstance.h"
#include "GameFramework/Character.h"
#include "Player/YggHero.h"
#include "PaperSpriteComponent.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Component/CaptureComponent.h"

// Sets default values
AYggMiniMapIconActor::AYggMiniMapIconActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComponent"));
	PaperSpriteComponent->SetupAttachment(DefaultScene);
	PaperSpriteComponent->SetRelativeRotation(FQuat::MakeFromEuler({ -90.0f, 0.0f, 90.0f }));
	PaperSpriteComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	PaperSpriteComponent->bVisibleInSceneCaptureOnly = true;
    
	RootComponent = DefaultScene;
}


// Called when the game starts or when spawned
void AYggMiniMapIconActor::BeginPlay()
{
	Super::BeginPlay();

    TryAddMiniMap();

    if (HasAuthority())
    {
        SetReplicates(true);
    }

    OnDestroyed.AddDynamic(this, &AYggMiniMapIconActor::OnIconDestroyed);
}

void AYggMiniMapIconActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    //if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    //{
    //    if (AMainGameHUD* HUD = Cast<AMainGameHUD>(PC->GetHUD()))
    //    {
    //        if (HUD->MiniMapManager)
    //        {
    //            HUD->MiniMapManager->RemoveMiniMapIcon(this);
    //        }
    //    }
    //}
}

// Called every frame
void AYggMiniMapIconActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (IsValid(AttachedCharacter))
    {
        FRotator NewRotation = AttachedCharacter->GetActorRotation();
        NewRotation.Pitch;
        NewRotation.Roll;
        NewRotation.Yaw;
        SetActorRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
    }
    else
    {
        FRotator CamRot = GetWorld()->GetFirstPlayerController()->GetControlRotation();
        SetActorRotation(FRotator(0.f, CamRot.Yaw, 0.f));
    }
}

void AYggMiniMapIconActor::SetPaperSprite(FName IConName)
{
    TMap<FName, UPaperSprite*>& IconData = UIDataAsset->IconSetting;

    if (IconData.Contains(IConName))
    {
        PaperSpriteComponent->SetSprite(IconData[IConName]);
    }
}

void AYggMiniMapIconActor::TryAddMiniMap()
{
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        if (AMainGameHUD* HUD = Cast<AMainGameHUD>(PC->GetHUD()))
        {
            if (HUD->MiniMapManager)
            {
                HUD->MiniMapManager->AddMiniMapIcon(this);
                return;
            }
        }
    }

    GetWorldTimerManager().SetTimerForNextTick(this, &AYggMiniMapIconActor::TryAddMiniMap);
}

void AYggMiniMapIconActor::SetAttachedCharacter(AActor* Character)
{
    AttachedCharacter = Character;
}

void AYggMiniMapIconActor::AddToCaptureComponent()
{
    if (AYggHero* Hero = Cast<AYggHero>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        if (UCaptureComponent* MinMapCapture = Hero->GetMiniMapCaptureComponent())
        {
            MinMapCapture->SetupMiniMapCapture(this);
        }
    }
}

void AYggMiniMapIconActor::OnIconDestroyed(AActor* DestroyedActor)
{
    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        if (AMainGameHUD* HUD = Cast<AMainGameHUD>(PC->GetHUD()))
        {
            if (HUD->MiniMapManager)
            {
                HUD->MiniMapManager->RemoveMiniMapIcon(this);
            }
        }
    }
}
