// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerBehaviorDependencies.generated.h"

class AProlabCharacter;

/**
 * 
 */
UCLASS()
class PROTOLAB_API UPlayerBehaviorDependencies : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(AProlabCharacter* Player);

	FORCEINLINE AProlabCharacter* GetPlayerCharacter() const { return PlayerCharacter; }

private:
	AProlabCharacter* PlayerCharacter = nullptr;
	
};
