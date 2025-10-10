// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerBehaviorSystem.h"
#include "Character/BehaviorConfig/PlayerBehaviorConfigBase.h"
#include "Character/BehaviorConfig/PlayerBehaviorDependencies.h"

UPlayerBehaviorSystem::UPlayerBehaviorSystem()
{
}

void UPlayerBehaviorSystem::Initialize(AProlabCharacter* PlayerCharacter)
{
	BehaviorConfigs.Empty();
	RuntimeConfigs.Empty();

	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::Initialize - PlayerCharacter is null"));
		return;
	}

	Dependencies = NewObject<UPlayerBehaviorDependencies>(this);
	Dependencies->Initialize(PlayerCharacter);
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

	if (Dependencies == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorSystem::AddBehaviorConfig - Dependencies is null, did you forget to call Initialize()?"));
		return;
	}

	auto Runtime = NewConfig->InitializeRuntime(Dependencies);
	if (Runtime)
	{
		BehaviorConfigs.Emplace(NewConfig);
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

