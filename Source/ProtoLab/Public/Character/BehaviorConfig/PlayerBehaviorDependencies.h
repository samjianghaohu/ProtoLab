// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerBehaviorDependencies.generated.h"

class AProlabCharacter;
class UInputComponent;
class UPlayerInputHandler;

/**
 * Dependencies class containing references needed by player behavior runtime logic.
 */
UCLASS()
class PROTOLAB_API UPlayerBehaviorDependencies : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(AProlabCharacter* Player);

	FORCEINLINE AProlabCharacter* GetPlayerCharacter() const { return PlayerCharacter; }

	FORCEINLINE UPlayerInputHandler* GetInputHandler() const { return InputHandler; }

private:
	AProlabCharacter* PlayerCharacter = nullptr;

	UPlayerInputHandler* InputHandler = nullptr;
};
