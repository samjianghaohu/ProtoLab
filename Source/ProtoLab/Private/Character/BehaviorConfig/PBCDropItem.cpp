// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BehaviorConfig/PBCDropItem.h"
#include "Character/BehaviorConfig/PlayerBehaviorDependencies.h"
#include "Character/ProlabCharacter.h"
#include "Character/PlayerInputHandler.h"
#include "Item/Item.h"
#include "PlayerInput/PlayerInputTypes.h"
#include "EnhancedInputSubsystems.h"

#pragma region Config Initialization

UPlayerBehaviorRuntimeConfigBase* UPbcDropItem::InitializeRuntimeInternal()
{
    return NewObject<UPbcDropItemRuntime>();
}

#pragma endregion

#pragma region Runtime Config

void UPbcDropItemRuntime::CacheConfigFromConfigBase()
{
	Config = Cast<UPbcDropItem>(ConfigBase);

	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPbcDropItemRuntime::Initialize - Config is null"));
		return;
	}

	// TODO: Move the following logic to a OnEnable function or something.
	if (Config->DropInputMapping != nullptr)
	{
		if (APlayerController* PlayerController = Cast<APlayerController>(Dependencies->GetPlayerCharacter()->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(Config->DropInputMapping, 1); // Make a priority enum for behavior inputs
			}
		}
	}
}

void UPbcDropItemRuntime::Update()
{
	// TODO: Make a generic state machine for behavior runtimes
	auto PlayerCharacter = Dependencies->GetPlayerCharacter();
	if (AItem* HeldItem = PlayerCharacter->GetHeldItem())
	{
		if (HeldItem->CanBeDropped(PlayerCharacter))
		{
			auto InputValue = Dependencies->GetInputHandler()->GetInputActionValue(EPlayerInputType::EPIA_Drop);
			if (InputValue.Get<bool>())
			{
				HeldItem->Drop(PlayerCharacter);
			}
		}
	}
}

#pragma endregion