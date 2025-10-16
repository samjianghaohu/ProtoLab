// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BehaviorConfig/ItemBehaviorConfigBase.h"
#include "IBCThrow.generated.h"

/**
 * Item behavior that lets the player throw the item with primary action.
 */
UCLASS()
class PROTOLAB_API UIbcThrow : public UItemBehaviorConfigBase
{
	GENERATED_BODY()

public:
#pragma region Configurable Fields
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* ThrowItemInputMapping = nullptr;
#pragma endregion

	virtual UItemBehaviorRuntimeConfigBase* InitializeRuntimeInternal() override;
};

UCLASS()
class PROTOLAB_API UIbcThrowRuntime : public UItemBehaviorRuntimeConfigBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(UItemBehaviorConfigBase* InConfigBase, UItemBehaviorDependencies* InBehaviorDependencies) override;
	virtual void CacheConfigFromConfigBase() override;
	virtual void Update() override;
	virtual void Dispose() override;

private:
	UIbcThrow* Config = nullptr;
	class APlayerController* PlayerController = nullptr;
};
