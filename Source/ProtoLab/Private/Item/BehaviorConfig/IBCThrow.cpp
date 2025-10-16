// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BehaviorConfig/IBCThrow.h"
#include "Item/BehaviorConfig/ItemBehaviorDependencies.h"
#include "Item/Item.h"
#include "Character/ProlabCharacter.h"
#include "EnhancedInputSubsystems.h"

#pragma region Config Initialization

UItemBehaviorRuntimeConfigBase* UIbcThrow::InitializeRuntimeInternal()
{
	return NewObject<UIbcThrowRuntime>();
}

#pragma endregion

#pragma region Runtime Config

void UIbcThrowRuntime::Initialize(UItemBehaviorConfigBase* InConfigBase, UItemBehaviorDependencies* InBehaviorDependencies)
{
	Super::Initialize(InConfigBase, InBehaviorDependencies);

	auto HolderPlayer = Dependencies->GetItem()->GetHolderPlayer();
	if (HolderPlayer != nullptr)
	{
		PlayerController = Cast<APlayerController>(HolderPlayer->GetController());
	}
}

void UIbcThrowRuntime::CacheConfigFromConfigBase()
{
	Config = Cast<UIbcThrow>(ConfigBase);

	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UIbcThrowRuntime::Initialize - Config is null"));
		return;
	}

	// TODO: Move the following logic to a OnEnable function or something.
	if (Config->ThrowItemInputMapping != nullptr && PlayerController != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Config->ThrowItemInputMapping, 2); // Make a priority enum for behavior inputs
		}
	}
}

void UIbcThrowRuntime::Update()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("UIbcThrowRuntime::Update")));
	}
}

void UIbcThrowRuntime::Dispose()
{
	if (Config->ThrowItemInputMapping != nullptr && PlayerController != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(Config->ThrowItemInputMapping);
		}
	}
}

#pragma endregion