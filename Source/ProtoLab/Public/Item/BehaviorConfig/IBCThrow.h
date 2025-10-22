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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UInputMappingContext* ThrowItemInputMapping = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UAnimMontage* ThrowAnimation = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ThrowAnimationPlayRate = 1.0f;

#pragma endregion

	virtual UItemBehaviorRuntimeConfigBase* InitializeRuntimeInternal() override;
};

UCLASS()
class PROTOLAB_API UIbcThrowRuntime : public UItemBehaviorRuntimeConfigBase
{
	GENERATED_BODY()

public:
	virtual void CacheConfigFromConfigBase() override;
	virtual void Update() override;
	virtual void Dispose() override;

private:
	UIbcThrow* Config = nullptr;
	class APlayerController* PlayerController = nullptr;

	bool bIsThrowAnimPlaying = false;

	bool CanHeldItemBeThrown();

	void PlayThrowAnimation();
	void OnThrowAnimationNotifyTriggered();
};
