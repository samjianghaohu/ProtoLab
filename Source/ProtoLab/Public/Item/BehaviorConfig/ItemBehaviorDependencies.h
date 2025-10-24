// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBehaviorDependencies.generated.h"

class AItem;
class AProlabCharacter;
class UPlayerInputHandler;
class UPlayerAnimInstance;

/**
 * Dependencies class containing references needed by item behavior runtime logic.
 */
UCLASS()
class PROTOLAB_API UItemBehaviorDependencies : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(AItem* InItem, AProlabCharacter* LocalPlayer);

	FORCEINLINE AItem* GetItem() const { return Item; }

	FORCEINLINE UPlayerInputHandler* GetInputHandler() const { return InputHandler; }

	FORCEINLINE UPlayerAnimInstance* GetPlayerAnimation() const { return PlayerAnimation; }

private:
	UPROPERTY()
	AItem* Item = nullptr;

	UPROPERTY()
	UPlayerInputHandler* InputHandler = nullptr;

	UPROPERTY()
	UPlayerAnimInstance* PlayerAnimation = nullptr;
};
