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
	virtual UPlayerBehaviorRuntimeConfigBase* InitializeRuntimeInternal() PURE_VIRTUAL(UPlayerBehaviorConfigBase::InitializeRuntimeInternal, return nullptr;)
};


UCLASS(Abstract)
class PROTOLAB_API UPlayerBehaviorRuntimeConfigBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(UPlayerBehaviorDependencies* BehaviorDependencies);

	virtual void Update() PURE_VIRTUAL(UPlayerBehaviorRuntimeConfigBase::Update)

protected:
	UPlayerBehaviorDependencies* Dependencies = nullptr;
};
