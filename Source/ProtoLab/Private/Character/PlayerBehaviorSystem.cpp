// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerBehaviorSystem.h"
#include "Character/BehaviorConfig/PlayerBehaviorConfigBase.h"

UPlayerBehaviorSystem::UPlayerBehaviorSystem()
{
}

void UPlayerBehaviorSystem::Initialize()
{
	BehaviorConfigs.Empty();
	RuntimeConfigs.Empty();
}

void UPlayerBehaviorSystem::Update(float DeltaTime)
{
	for (UPlayerBehaviorRuntimeConfigBase* RuntimeConfig : RuntimeConfigs)
	{
		if (RuntimeConfig)
		{
			RuntimeConfig->Update();
		}
	}
}

void UPlayerBehaviorSystem::AddBehaviorConfig(UPlayerBehaviorConfigBase* NewConfig)
{
	if (NewConfig == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::AddBehaviorConfig - NewConfig is null"));
		return;
	}

	BehaviorConfigs.Add(NewConfig);
	auto Runtime = NewConfig->InitializeRuntime();
	if (Runtime)
	{
		Runtime->Initialize();
		RuntimeConfigs.Emplace(Runtime);
	}
}

void UPlayerBehaviorSystem::RemoveBehaviorConfig(UPlayerBehaviorConfigBase* ConfigToRemove)
{
	if (ConfigToRemove == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::RemoveBehaviorConfig - ConfigToRemove is null"));
		return;
	}
}

