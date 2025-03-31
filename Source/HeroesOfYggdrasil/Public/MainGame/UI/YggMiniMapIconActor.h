// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "MainGame/UI/YggUIDataAsset.h"
#include "YggMiniMapIconActor.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AYggMiniMapIconActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYggMiniMapIconActor();

	void SetPaperSprite(AActor* Actor);

	UPaperSpriteComponent* GetPaperSpriteComponent()
	{
		return PaperSpriteComponent;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YGG", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultScene = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YGG", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* PaperSpriteComponent = nullptr;
	
	UPROPERTY(EditAnywhere)
	UYggUIDataAsset* UIDataAsset;
};
