// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BehaviorConfig/PlayerBehaviorConfigBase.h"

UPlayerBehaviorRuntimeConfigBase* UPlayerBehaviorConfigBase::InitializeRuntime(UPlayerBehaviorDependencies* BehaviorDependencies)
{
	UPlayerBehaviorRuntimeConfigBase* Runtime = InitializeRuntimeInternal();

	if (Runtime == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerBehaviorConfigBase::InitializeRuntime - Fail to create Runtime"));
		return nullptr;
	}

	Runtime->Initialize(BehaviorDependencies);
	return Runtime;
}

void UPlayerBehaviorRuntimeConfigBase::Initialize(UPlayerBehaviorDependencies* BehaviorDependencies)
{
	Dependencies = BehaviorDependencies;
}