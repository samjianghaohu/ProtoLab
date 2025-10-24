// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemBehaviorConfigBase.generated.h"

class UItemBehaviorDependencies;

/**
 * Base class for all item behavior config data assets.
 */
UCLASS(Abstract)
class PROTOLAB_API UItemBehaviorConfigBase : public UDataAsset
{
	GENERATED_BODY()

public:
	UItemBehaviorRuntimeConfigBase* InitializeRuntime(UItemBehaviorDependencies* BehaviorDependencies);

private:
	// Child classes must implement this to return their own runtime config instance.
	virtual UItemBehaviorRuntimeConfigBase* InitializeRuntimeInternal() PURE_VIRTUAL(UItemBehaviorConfigBase::InitializeRuntimeInternal, return nullptr;)
};

/**
 * Base class for all item behavior runtime config instances.
 * Instantiated from an item behavior config data asset, and initialized with item behavior dependencies.
 */
UCLASS(Abstract)
class PROTOLAB_API UItemBehaviorRuntimeConfigBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(UItemBehaviorConfigBase* InConfigBase, UItemBehaviorDependencies* InBehaviorDependencies);

	virtual void OnEnable() PURE_VIRTUAL(UItemBehaviorRuntimeConfigBase::OnEnable)

	virtual void Update() PURE_VIRTUAL(UItemBehaviorRuntimeConfigBase::Update)

	virtual void Dispose() PURE_VIRTUAL(UItemBehaviorRuntimeConfigBase::Dispose)

protected:
	UItemBehaviorDependencies* Dependencies = nullptr;

	UItemBehaviorConfigBase* ConfigBase = nullptr;

	// Since child runtime configs will need their own concrete config not just the config base, and that we couldn't make runtime config base a template,
	// We force child classes to implement this function to cache their own config from the base config.
	virtual void CacheConfigFromConfigBase() PURE_VIRTUAL(UItemBehaviorRuntimeConfigBase::CacheConfigFromConfigBase)
};
