// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BehaviorConfig/PlayerBehaviorConfigBase.h"
#include "PBCDropItem.generated.h"

/**
 * 
 */
UCLASS()
class PROTOLAB_API UPbcDropItem : public UPlayerBehaviorConfigBase
{
	GENERATED_BODY()

public:
#pragma region Configurable Fields
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* DropInputMapping = nullptr;
#pragma endregion

	virtual UPlayerBehaviorRuntimeConfigBase* InitializeRuntimeInternal() override;

};

UCLASS()
class PROTOLAB_API UPbcDropItemRuntime : public UPlayerBehaviorRuntimeConfigBase
{
	GENERATED_BODY()

public:
	virtual void CacheConfigFromConfigBase() override;
	virtual void Update() override;

private:
	UPbcDropItem* Config = nullptr;
};


