// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YggMiniMapManager.generated.h"

class UCaptureComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROESOFYGGDRASIL_API UYggMiniMapManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UYggMiniMapManager();

	void AddMiniMapIcon(AActor* Icon);
	void RemoveMiniMapIcon(AActor* Icon);
	
	void UpdateShowOnlyActors();

	TArray<TWeakObjectPtr<AActor>>& GetMiniMapIcons()
	{
		return MiniMapIconActors;
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> MiniMapIconActors;
};
