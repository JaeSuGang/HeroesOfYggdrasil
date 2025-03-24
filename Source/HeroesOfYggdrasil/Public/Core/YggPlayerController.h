// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "YggPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UENUM()
enum class EInputMappingContextPriority
{
	Character,
	Controller,
	UIMode
};

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AYggPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void SetupInputComponent() override;
	void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Exec)
	void TestTakeDamage(float fDamage);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SetGenericTeamId(const FGenericTeamId& _TeamID) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetMouseMode(const FInputActionValue& Value, bool bIsMouseModeOn);

	FGenericTeamId GetGenericTeamId() const override;

	void SetInputEnabled(bool Value);

protected:
	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	FGenericTeamId TeamID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* DefaultMappingContext;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* UIModeMappingContext;

	UPROPERTY()
	UInputMappingContext* CharacterMappingContextToRestore;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* InputModeAction;
};
