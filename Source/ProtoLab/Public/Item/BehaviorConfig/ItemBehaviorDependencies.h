// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBehaviorDependencies.generated.h"

class AItem;
class UPlayerInputHandler;

/**
 * Dependencies class containing references needed by item behavior runtime logic.
 */
UCLASS()
class PROTOLAB_API UItemBehaviorDependencies : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(AItem* InItem, UPlayerInputHandler* InInputHandler);

	FORCEINLINE AItem* GetItem() const { return Item; }

	FORCEINLINE UPlayerInputHandler* GetInputHandler() const { return InputHandler; }

private:
	AItem* Item = nullptr;

	UPlayerInputHandler* InputHandler = nullptr;

};
