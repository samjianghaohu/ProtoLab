// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerInputTypes.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerInputConfig.generated.h"

/**
 * An asset that holds configuration data for all available player input actions.
 */
UCLASS()
class PROTOLAB_API UPlayerInputConfigs : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FPlayerInputConfig> PlayerInputConfigs;
};
