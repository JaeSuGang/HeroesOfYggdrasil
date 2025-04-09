// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MHPBarComponent.generated.h"

class UYggMHPBarUserWidget;
class UWidgetComponent;
class AEnemyCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROESOFYGGDRASIL_API UMHPBarComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMHPBarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> MHPBarWidgetClass;

	UPROPERTY()
	UYggMHPBarUserWidget* MHPBarWidget;

	UPROPERTY()
	UWidgetComponent* MHPBarWidgetComponent;

	UPROPERTY()
	AEnemyCharacter* EnemyCharacter;
};
