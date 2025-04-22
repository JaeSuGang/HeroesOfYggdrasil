// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMiniMapManager.h"
#include "Component/CaptureComponent.h"
#include "Player/YggHero.h"

// Sets default values for this component's properties
UYggMiniMapManager::UYggMiniMapManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UYggMiniMapManager::AddMiniMapIcon(AActor* Icon)
{
	if (!Icon || MiniMapIconActors.Contains(Icon))
		return;

	MiniMapIconActors.Add(Icon);
	UpdateShowOnlyActors();
}

void UYggMiniMapManager::RemoveMiniMapIcon(AActor* Icon)
{
	if (!Icon)
		return;

	MiniMapIconActors.Remove(Icon);
	UpdateShowOnlyActors();
}

void UYggMiniMapManager::UpdateShowOnlyActors()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (AYggHero* Hero = PC->GetPawn<AYggHero>())
		{
			if (UCaptureComponent* Capture = Hero->GetMiniMapCaptureComponent())
			{
				Capture->ShowOnlyActors.Empty();

				for (const auto& IconActor : MiniMapIconActors)
				{
					if (IconActor.IsValid())
					{
						Capture->ShowOnlyActors.Add(IconActor.Get());
					}
				}
			}
		}
	}
}


// Called when the game starts
void UYggMiniMapManager::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UYggMiniMapManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

