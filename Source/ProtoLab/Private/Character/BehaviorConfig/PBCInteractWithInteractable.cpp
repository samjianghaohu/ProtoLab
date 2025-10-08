// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BehaviorConfig/PBCInteractWithInteractable.h"

#pragma region Config Initialization

UPlayerBehaviorRuntimeConfigBase* UPbcInteractWithInteractable::InitializeRuntime()
{
	return NewObject<UPbcInteractWithInteractableRuntime>();
}

#pragma endregion

#pragma region Runtime Config


void UPbcInteractWithInteractableRuntime::Initialize()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacting with interactable Initialized!"));
	}
}

void UPbcInteractWithInteractableRuntime::Update()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, TEXT("Interacting with interactable Update!"));
	}
}

#pragma endregion