#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class FUpgradeDataAssetDetailCustomization : public IDetailCustomization
{
public:
	FReply OnClickedAddToTable();

	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static TSharedRef<IDetailCustomization> MakeInstance();
};