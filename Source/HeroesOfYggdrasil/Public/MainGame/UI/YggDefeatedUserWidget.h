// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggDefeatedUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggDefeatedUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:


protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;


private:


};
