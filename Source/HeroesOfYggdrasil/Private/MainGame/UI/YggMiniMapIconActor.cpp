// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMiniMapIconActor.h"
#include "MainGame/UI/YggUIDataAsset.h"
#include "Core/YggGameInstance.h"
#include "GameFramework/Character.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"

// Sets default values
AYggMiniMapIconActor::AYggMiniMapIconActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	PaperSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperSpriteComponent"));
	PaperSpriteComponent->SetupAttachment(DefaultScene);
	PaperSpriteComponent->SetRelativeRotation(FQuat::MakeFromEuler({ 90.0f, 0.0f, 0.0f }));
	PaperSpriteComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	PaperSpriteComponent->bVisibleInSceneCaptureOnly = true;

	RootComponent = DefaultScene;
}


// Called when the game starts or when spawned
void AYggMiniMapIconActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYggMiniMapIconActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AYggMiniMapIconActor::SetPaperSprite(AActor* Actor)
{
    if (!Actor || !UIDataAsset) return;

    ACharacter* Character = Cast<ACharacter>(Actor);
    if (!Character) return; // ACharacter가 아니면 함수 종료

    TMap<FName, UPaperSprite*>& IconData = UIDataAsset->IconSetting;

    for (TPair<FName, UPaperSprite*>& Icon : IconData)
    {
        AYggHero* Hero = Cast<AYggHero>(Character);
        if (!IsValid(Hero)) continue;

        if (Hero->GetHeroAttributeComponent()->HasTagExact(Icon.Key))
        {
            PaperSpriteComponent->SetSprite(Icon.Value);
            break;
        }
    }
}