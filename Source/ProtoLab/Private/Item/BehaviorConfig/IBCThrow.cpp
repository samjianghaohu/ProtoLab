// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BehaviorConfig/IBCThrow.h"
#include "Item/BehaviorConfig/ItemBehaviorDependencies.h"
#include "Item/Item.h"
#include "Character/ProlabCharacter.h"
#include "Character/PlayerInputHandler.h"
#include "PlayerInput/PlayerInputTypes.h"
#include "Animation/AnimNotifyWithDelegates.h"
#include "Animation/AnimMontage.h"
#include "EnhancedInputSubsystems.h"

#pragma region Config Initialization

UItemBehaviorRuntimeConfigBase* UIbcThrow::InitializeRuntimeInternal()
{
	return NewObject<UIbcThrowRuntime>();
}

#pragma endregion

#pragma region Runtime Config

void UIbcThrowRuntime::CacheConfigFromConfigBase()
{
	Config = Cast<UIbcThrow>(ConfigBase);

	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UIbcThrowRuntime::Initialize - Config is null"));
		return;
	}

	auto HolderPlayer = Dependencies->GetItem()->GetHolderPlayer();
	if (HolderPlayer != nullptr)
	{
		PlayerController = Cast<APlayerController>(HolderPlayer->GetController());
	}

	// TODO: Move the following logic to a OnEnable function or something.
	if (Config->ThrowItemInputMapping != nullptr && PlayerController != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Config->ThrowItemInputMapping, 2); // Make a priority enum for behavior inputs
		}
	}

	bIsThrowAnimPlaying = false;
}

void UIbcThrowRuntime::Update()
{
	if (bIsThrowAnimPlaying)
	{
		return;
	}

	auto InputValue = Dependencies->GetInputHandler()->GetInputActionValue(EPlayerInputType::EPIA_PrimaryAction);
	if (InputValue.Get<bool>() && CanHeldItemBeThrown())
	{
		bIsThrowAnimPlaying = true;
		PlayThrowAnimation();
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

bool UIbcThrowRuntime::CanHeldItemBeThrown()
{
	auto Item = Dependencies->GetItem();
	if (Item == nullptr)
	{
		return false;
	}

	auto HolderPlayer = Item->GetHolderPlayer();
	if (HolderPlayer == nullptr)
	{
		return false;
	}

	return Item->CanBeDropped(HolderPlayer);
}

void UIbcThrowRuntime::PlayThrowAnimation()
{
	auto HolderPlayer = Dependencies->GetItem()->GetHolderPlayer();
	if (HolderPlayer != nullptr && Config->ThrowAnimation != nullptr)
	{
		const TArray<FAnimNotifyEvent> NotifyEvents = Config->ThrowAnimation->Notifies;
		if (NotifyEvents.Num() > 0)
		{
			if (const auto Notify = Cast<UAnimNotifyWithDelegates>(NotifyEvents[0].Notify))
			{
				Notify->OnNotified.AddUObject(this, &UIbcThrowRuntime::OnThrowAnimationNotifyTriggered);
			}
		}

		HolderPlayer->PlayAnimMontage(Config->ThrowAnimation, Config->ThrowAnimationPlayRate);
	}
}

void UIbcThrowRuntime::OnThrowAnimationNotifyTriggered()
{
	const TArray<FAnimNotifyEvent> NotifyEvents = Config->ThrowAnimation->Notifies;
	if (NotifyEvents.Num() > 0)
	{
		if (const auto Notify = Cast<UAnimNotifyWithDelegates>(NotifyEvents[0].Notify))
		{
			Notify->OnNotified.RemoveAll(this);
		}
	}

	auto Item = Dependencies->GetItem();
	auto HolderPlayer = Item->GetHolderPlayer();

	auto ReleaseDirection = HolderPlayer->GetActorForwardVector(); // For simplicity, just use character forward as throw direction, we can do something more complicated later.
	Item->Drop(ReleaseDirection, Config->ThrowReleaseSpeed);
}

#pragma endregion