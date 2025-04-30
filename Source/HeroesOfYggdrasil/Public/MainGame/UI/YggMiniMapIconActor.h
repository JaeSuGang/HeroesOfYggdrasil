// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainGame/UI/YggUIDataAsset.h"
#include "YggMiniMapIconActor.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AYggMiniMapIconActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYggMiniMapIconActor();

	void SetPaperSprite(FName IConName);

	void TryAddMiniMap();

	class UPaperSpriteComponent* GetPaperSpriteComponent()
	{
		return PaperSpriteComponent;
	}

	void SetAttachedCharacter(AActor* Character);

	void AddToCaptureComponent();

	UFUNCTION(BlueprintCallable)
	void OnIconDestroyed(AActor* DestroyedActor);

protected:
	// Called when the game starts or when spawned
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "YGG", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DefaultScene = nullptr;

	UPROPERTY(VisibleAnywhere, Replicated, BlueprintReadOnly, Category = "YGG", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* PaperSpriteComponent = nullptr;
	
	UPROPERTY(EditAnywhere)
	UYggUIDataAsset* UIDataAsset;

	UPROPERTY(EditAnywhere)
	AActor* AttachedCharacter;
};
