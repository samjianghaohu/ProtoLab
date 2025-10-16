// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerBehaviorSystem.generated.h"

class UPlayerBehaviorConfigBase;
class UItemBehaviorConfigBase;
class AItem;

UCLASS(ClassGroup = (Custom))
class PROTOLAB_API UPlayerBehaviorSystem : public UObject
{
	GENERATED_BODY()

public:	
	UPlayerBehaviorSystem();

	void Initialize(class AProlabCharacter* PlayerCharacter);

	void Update(float DeltaTime);

#pragma region Global Player Behavior
	void AddGlobalPlayerBehaviorConfig(UPlayerBehaviorConfigBase* NewConfig);
	void RemoveGlobalPlayerBehaviorConfig(UPlayerBehaviorConfigBase* ConfigToRemove);
#pragma endregion

#pragma region Item Behavior
	void AddItemBehaviorConfig(AItem* Item);
	void RemoveItemBehaviorConfig(AItem* Item);
#pragma endregion


private:
	UPROPERTY(VisibleAnywhere, Category = Behavior)
	TArray<UPlayerBehaviorConfigBase*> GlobalBehaviorConfigs;

	UPROPERTY(VisibleAnywhere, Category = Behavior)
	TArray<class UPlayerBehaviorRuntimeConfigBase*> GlobalRuntimeConfigs;

	UPROPERTY(VisibleAnywhere, Category = Behavior)
	TArray<UItemBehaviorConfigBase*> ItemBehaviorConfigs;

	UPROPERTY(VisibleAnywhere, Category = Behavior)
	TArray<class UItemBehaviorRuntimeConfigBase*> ItemRuntimeConfigs;

	class UPlayerBehaviorDependencies* PlayerBehaviorDependencies = nullptr;

	class AProlabCharacter* Player = nullptr;

	void UpdateGlobalBehaviors(float DeltaTime);

	void UpdateItemBehaviors(float DeltaTime);
};
