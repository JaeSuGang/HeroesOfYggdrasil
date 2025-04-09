// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggNicknameBarUserWidget.generated.h"

class UTextBlock;
class UNicknameBarComponent;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggNicknameBarUserWidget : public UYggUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerName;

	UFUNCTION()
	void SetPlayerName();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY()
	UNicknameBarComponent* NicknameBarComponent;
};
