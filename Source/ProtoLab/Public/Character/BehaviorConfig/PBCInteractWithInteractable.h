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
#pragma region Configurable Fields
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* InteractInputMapping = nullptr;
#pragma endregion

	virtual UPlayerBehaviorRuntimeConfigBase* InitializeRuntimeInternal() override;

};

UCLASS()
class PROTOLAB_API UPbcInteractWithInteractableRuntime : public UPlayerBehaviorRuntimeConfigBase
{
	GENERATED_BODY()

public:
	virtual void CacheConfigFromConfigBase() override;
	virtual void Update() override;

private:
	UPbcInteractWithInteractable* Config = nullptr;
};
