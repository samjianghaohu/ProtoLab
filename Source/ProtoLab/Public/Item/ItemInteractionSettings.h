#pragma once

#include "CoreMinimal.h"
#include "ItemInteractionSettings.generated.h"

USTRUCT(BlueprintType)
struct FItemInteractionSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UItemBehaviorConfigBase* ItemBehaviorConfig;
};