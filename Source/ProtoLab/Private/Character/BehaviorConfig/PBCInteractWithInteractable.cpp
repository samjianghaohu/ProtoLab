// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BehaviorConfig/PBCInteractWithInteractable.h"
#include "Character/BehaviorConfig/PlayerBehaviorDependencies.h"
#include "Character/PlayerInputHandler.h"
#include "Character/ProlabCharacter.h"
#include "EnhancedInputSubsystems.h"

#pragma region Config Initialization

UPlayerBehaviorRuntimeConfigBase* UPbcInteractWithInteractable::InitializeRuntimeInternal()
{
	return NewObject<UPbcInteractWithInteractableRuntime>();
}

#pragma endregion

#pragma region Runtime Config


void UPbcInteractWithInteractableRuntime::CacheConfigFromConfigBase()
{
	Config = Cast<UPbcInteractWithInteractable>(ConfigBase);

	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPbcInteractWithInteractableRuntime::Initialize - Config is null"));
		return;
	}

	// TODO: Move the following logic to a OnEnable function or something.
	if (Config->InteractInputMapping != nullptr)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(Dependencies->GetPlayerCharacter()->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(Config->InteractInputMapping, 1);
			}
		}
	}
}

void UPbcInteractWithInteractableRuntime::Update()
{
	auto InputValue = Dependencies->GetInputHandler()->GetInteractActionValue();
	if (InputValue.Get<bool>())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, TEXT("Interacting with interactable!"));
		}
	}
}

#pragma endregion