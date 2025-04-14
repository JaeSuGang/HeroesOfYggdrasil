// Copyright Epic Games, Inc. All Rights Reserved.

#include "HeroesOfYggdrasilEditor.h"

#include "PropertyEditorModule.h"

#include "UpgradeSystem/UpgradeDataAsset.h"
#include "UpgradeSystem/UpgradeDataAssetPanel.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FHeroesOfYggdrasilEditorModule, HeroesOfYggdrasilEditor, "HeroesOfYggdrasilEditor" );

void FHeroesOfYggdrasilEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.RegisterCustomClassLayout(UUpgradeDataAsset::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FUpgradeDataAssetDetailCustomization::MakeInstance));
}

void FHeroesOfYggdrasilEditorModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.UnregisterCustomClassLayout(UUpgradeDataAsset::StaticClass()->GetFName());
}
