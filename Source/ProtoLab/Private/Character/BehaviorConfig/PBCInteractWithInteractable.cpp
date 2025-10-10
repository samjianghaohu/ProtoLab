// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BehaviorConfig/PBCInteractWithInteractable.h"
#include "Character/BehaviorConfig/PlayerBehaviorDependencies.h"	

#pragma region Config Initialization

UPlayerBehaviorRuntimeConfigBase* UPbcInteractWithInteractable::InitializeRuntimeInternal()
{
	return NewObject<UPbcInteractWithInteractableRuntime>();
}

#pragma endregion

#pragma region Runtime Config


void UPbcInteractWithInteractableRuntime::Initialize(UPlayerBehaviorDependencies* BehaviorDependencies)
{
	Super::Initialize(BehaviorDependencies);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacting with interactable Initialized!"));
	}
}

void UPbcInteractWithInteractableRuntime::Update()
{
	bool bIsValid = Dependencies && Dependencies->GetPlayerCharacter();


	if (bIsValid && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, TEXT("Interacting with interactable Update with valid player"));
	}
}

#pragma endregion