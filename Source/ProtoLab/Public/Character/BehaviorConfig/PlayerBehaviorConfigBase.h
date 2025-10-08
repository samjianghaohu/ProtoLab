// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerBehaviorConfigBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROTOLAB_API UPlayerBehaviorConfigBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual UPlayerBehaviorRuntimeConfigBase* InitializeRuntime() PURE_VIRTUAL(UPlayerBehaviorConfigBase::InitializeRuntime, return nullptr;)
};


UCLASS(Abstract)
class PROTOLAB_API UPlayerBehaviorRuntimeConfigBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize() PURE_VIRTUAL(UPlayerBehaviorRuntimeConfigBase::Initialize)

	virtual void Update() PURE_VIRTUAL(UPlayerBehaviorRuntimeConfigBase::Update)
};
