// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerBehaviorConfigBase.generated.h"

class UPlayerBehaviorDependencies;

/**
 * 
 */
UCLASS(Abstract)
class PROTOLAB_API UPlayerBehaviorConfigBase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPlayerBehaviorRuntimeConfigBase* InitializeRuntime(UPlayerBehaviorDependencies* BehaviorDependencies);

private:
	// Child classes must implement this to return their own runtime config instance.
	virtual UPlayerBehaviorRuntimeConfigBase* InitializeRuntimeInternal() PURE_VIRTUAL(UPlayerBehaviorConfigBase::InitializeRuntimeInternal, return nullptr;)
};


UCLASS(Abstract)
class PROTOLAB_API UPlayerBehaviorRuntimeConfigBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(UPlayerBehaviorConfigBase* Config, UPlayerBehaviorDependencies* BehaviorDependencies);

	virtual void Update() PURE_VIRTUAL(UPlayerBehaviorRuntimeConfigBase::Update)

protected:
	UPlayerBehaviorDependencies* Dependencies = nullptr;

	UPlayerBehaviorConfigBase* ConfigBase = nullptr;

	// Since child runtime configs will need their own concrete config not just the config base, and that we couldn't make runtime config base a template,
	// We force child classes to implement this function to cache their own config from the base config.
	virtual void CacheConfigFromConfigBase() PURE_VIRTUAL(UPlayerBehaviorRuntimeConfigBase::CacheConfigFromConfigBase)
};
