// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BehaviorConfig/ItemBehaviorConfigBase.h"
#include "IBCMeleeWeapon.generated.h"

/**
 * Item behavior shared among all melee weapons.
 */
UCLASS()
class PROTOLAB_API UIbcMeleeWeapon : public UItemBehaviorConfigBase
{
	GENERATED_BODY()

public:
#pragma region Configurable Fields

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* MeleeWeaponInputMapping = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	class UAnimMontage* IdleAnimation = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	class UAnimMontage* SwingAnimation = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	float SwingAnimationPlayRate = 1.0f;

#pragma endregion

	virtual UItemBehaviorRuntimeConfigBase* InitializeRuntimeInternal() override;
};

UCLASS()
class PROTOLAB_API UIbcMeleeWeaponRuntime : public UItemBehaviorRuntimeConfigBase
{
	GENERATED_BODY()

public:
	virtual void CacheConfigFromConfigBase() override;
	virtual void Update() override;
	virtual void Dispose() override;

private:
	UPROPERTY()
	UIbcMeleeWeapon* Config = nullptr;

	UPROPERTY()
	class APlayerController* PlayerController = nullptr;

	bool bIsSwingAnimationPlaying = false;

	void PlaySwingAnimation();

	void OnSwingAnimationNotifyTriggered();
};
