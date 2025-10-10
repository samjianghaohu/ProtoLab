// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BehaviorConfig/PlayerBehaviorConfigBase.h"
#include "PBCInteractWithInteractable.generated.h"

/**
 * 
 */
UCLASS()
class PROTOLAB_API UPbcInteractWithInteractable : public UPlayerBehaviorConfigBase
{
	GENERATED_BODY()

public:
	virtual UPlayerBehaviorRuntimeConfigBase* InitializeRuntimeInternal() override;

};

UCLASS()
class PROTOLAB_API UPbcInteractWithInteractableRuntime : public UPlayerBehaviorRuntimeConfigBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(UPlayerBehaviorDependencies* BehaviorDependencies) override;
	virtual void Update() override;
};
