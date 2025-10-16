// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PlayerBehaviorSystem.h"
#include "Character/ProlabCharacter.h"
#include "Character/BehaviorConfig/PlayerBehaviorConfigBase.h"
#include "Character/BehaviorConfig/PlayerBehaviorDependencies.h"
#include "Item/Item.h"
#include "Item/BehaviorConfig/ItemBehaviorDependencies.h"
#include "Item/BehaviorConfig/ItemBehaviorConfigBase.h"

UPlayerBehaviorSystem::UPlayerBehaviorSystem()
{
}

void UPlayerBehaviorSystem::Initialize(AProlabCharacter* PlayerCharacter)
{
	GlobalBehaviorConfigs.Empty();
	GlobalRuntimeConfigs.Empty();

	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::Initialize - PlayerCharacter is null"));
		return;
	}

	Player = PlayerCharacter;
	PlayerBehaviorDependencies = NewObject<UPlayerBehaviorDependencies>(this);
	PlayerBehaviorDependencies->Initialize(PlayerCharacter);
}

void UPlayerBehaviorSystem::Update(float DeltaTime)
{
	UpdateGlobalBehaviors(DeltaTime);
	UpdateItemBehaviors(DeltaTime);
}

#pragma region Global Player Behavior

void UPlayerBehaviorSystem::AddGlobalPlayerBehaviorConfig(UPlayerBehaviorConfigBase* NewConfig)
{
	if (NewConfig == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::AddBehaviorConfig - NewConfig is null"));
		return;
	}

	if (PlayerBehaviorDependencies == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::AddBehaviorConfig - Dependencies is null, did you forget to call Initialize()?"));
		return;
	}

	auto Runtime = NewConfig->InitializeRuntime(PlayerBehaviorDependencies);
	if (Runtime)
	{
		GlobalBehaviorConfigs.Emplace(NewConfig);
		GlobalRuntimeConfigs.Emplace(Runtime);
	}
}

void UPlayerBehaviorSystem::RemoveGlobalPlayerBehaviorConfig(UPlayerBehaviorConfigBase* ConfigToRemove)
{
	if (ConfigToRemove == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::RemoveBehaviorConfig - ConfigToRemove is null"));
		return;
	}
}

void UPlayerBehaviorSystem::UpdateGlobalBehaviors(float DeltaTime)
{
	for (UPlayerBehaviorRuntimeConfigBase* RuntimeConfig : GlobalRuntimeConfigs)
	{
		if (RuntimeConfig)
		{
			RuntimeConfig->Update();
		}
	}
}

#pragma endregion

#pragma region Item Behavior

void UPlayerBehaviorSystem::AddItemBehaviorConfig(AItem* Item)
{
	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::AddItemBehaviorConfig - Item is null"));
		return;
	}

	auto NewConfig = Item->GetItemBehaviorConfig();
	if (NewConfig == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::AddItemBehaviorConfig - NewConfig is null on item: %s"), *Item->GetName());
		return;
	}

	if (Player == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::AddItemBehaviorConfig - No player is cached."));
		return;
	}

	auto InputHandler = Player->GetInputHandler();
	if (InputHandler == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::AddItemBehaviorConfig - Player has no InputHandler. Something is wrong."));
		return;
	}

	auto Dependencies = NewObject<UItemBehaviorDependencies>(this);
	Dependencies->Initialize(Item, InputHandler);

	auto Runtime = NewConfig->InitializeRuntime(Dependencies);
	if (Runtime)
	{
		// Cache the runtime behavior in the item so we have the reference when trying to remove it.
		Item->CacheRuntimeBehavior(Runtime);

		ItemBehaviorConfigs.Emplace(NewConfig);
		ItemRuntimeConfigs.Emplace(Runtime);
	}
}

void UPlayerBehaviorSystem::RemoveItemBehaviorConfig(AItem* Item)
{
	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::RemoveItemBehaviorConfig - Item is null"));
		return;
	}

	auto RuntimeToRemove = Item->GetCachedRuntimeBehavior();
	if (RuntimeToRemove == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::RemoveItemBehaviorConfig - Item %s has no cached runtime behavior"), *Item->GetName());
		return;
	}

	auto ConfigToRemove = Item->GetItemBehaviorConfig();
	if (ConfigToRemove == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::RemoveItemBehaviorConfig - Item %s has no behavior config"), *Item->GetName());
		return;
	}

	Item->CacheRuntimeBehavior(nullptr);

	ItemRuntimeConfigs.Remove(RuntimeToRemove);
	ItemBehaviorConfigs.Remove(ConfigToRemove);

	RuntimeToRemove->Dispose();
}

void UPlayerBehaviorSystem::UpdateItemBehaviors(float DeltaTime)
{
	for (UItemBehaviorRuntimeConfigBase* RuntimeConfig : ItemRuntimeConfigs)
	{
		if (RuntimeConfig)
		{
			RuntimeConfig->Update();
		}
	}
}

#pragma endregion
