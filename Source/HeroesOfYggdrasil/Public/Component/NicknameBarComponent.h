// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "NicknameBarComponent.generated.h"

class UWidgetComponent;
class UYggNicknameBarUserWidget;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROESOFYGGDRASIL_API UNicknameBarComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNicknameBarComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<UUserWidget> NicknameBarWidgetClass;

	UPROPERTY()
	UYggNicknameBarUserWidget* NicknameBarWidget;

	UPROPERTY()
	UWidgetComponent* NicknameBarWidgetComponent;


};
