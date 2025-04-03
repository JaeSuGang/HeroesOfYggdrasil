#include "Upgrade/UpgradeDataAssetPanel.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

FReply FUpgradeDataAssetDetailCustomization::OnClickedAddToTable()
{
	return FReply::Handled();
}

void FUpgradeDataAssetDetailCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(TEXT("Upgrade Editor Tool"));

	FDetailWidgetRow& CustomRow = Category.AddCustomRow(FText::FromString("Hello"));

	CustomRow
		.NameContent()
		[
			SNew(STextBlock)
				.Text(FText::FromString(TEXT("Register To DataTable")))
				.Font(IDetailLayoutBuilder::GetDetailFont())
		];

	CustomRow
		.ValueContent()
		[
			SNew(SButton)
				.Text(FText::FromString(TEXT("Register")))
				.OnClicked(FOnClicked::CreateSP(this, &FUpgradeDataAssetDetailCustomization::OnClickedAddToTable))
		];
}

TSharedRef<IDetailCustomization> FUpgradeDataAssetDetailCustomization::MakeInstance()
{
	return MakeShareable(new FUpgradeDataAssetDetailCustomization());
}
