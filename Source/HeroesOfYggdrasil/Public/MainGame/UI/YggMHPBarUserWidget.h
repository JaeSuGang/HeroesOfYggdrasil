// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggMHPBarUserWidget.generated.h"

class UProgressBar;
class AEnemyCharacter;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggMHPBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeOnInitialized() override;
	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateHPBar(float HP);

	UFUNCTION(BlueprintCallable)
	void SetAttachedCharacter(AActor* Character);

	UPROPERTY()
	AEnemyCharacter* EnemyCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Owner")
	AActor* OwningActor;

	void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }
	class UWidgetComponent* GetOwningWidgetComponent();
	AActor* GetOwningActorFromWidget(UUserWidget* Widget);

public:
	void Test();

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;
};
