// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BehaviorConfig/ItemBehaviorConfigBase.h"

UItemBehaviorRuntimeConfigBase* UItemBehaviorConfigBase::InitializeRuntime(UItemBehaviorDependencies* BehaviorDependencies)
{
	UItemBehaviorRuntimeConfigBase* Runtime = InitializeRuntimeInternal();

	if (Runtime == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UItemBehaviorConfigBase::InitializeRuntime - Fail to create Runtime"));
		return nullptr;
	}

	Runtime->Initialize(this, BehaviorDependencies);
	return Runtime;
}

void UItemBehaviorRuntimeConfigBase::Initialize(UItemBehaviorConfigBase* InConfigBase, UItemBehaviorDependencies* InBehaviorDependencies)
{
	Dependencies = InBehaviorDependencies;
	ConfigBase = InConfigBase;

	CacheConfigFromConfigBase();

	OnEnable();
}
