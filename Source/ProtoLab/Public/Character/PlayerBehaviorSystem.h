// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBehaviorSystem.generated.h"

class UPlayerBehaviorConfigBase;

UCLASS(ClassGroup = (Custom))
class PROTOLAB_API UPlayerBehaviorSystem : public UObject
{
	GENERATED_BODY()

public:	
	UPlayerBehaviorSystem();

	void Initialize();

	void Update(float DeltaTime);

	void AddBehaviorConfig(UPlayerBehaviorConfigBase* NewConfig);

	void RemoveBehaviorConfig(UPlayerBehaviorConfigBase* ConfigToRemove);

private:
	UPROPERTY(VisibleAnywhere, Category = Behavior)
	TArray<UPlayerBehaviorConfigBase*> BehaviorConfigs;

	UPROPERTY(VisibleAnywhere, Category = Behavior)
	TArray<class UPlayerBehaviorRuntimeConfigBase*> RuntimeConfigs;
};
