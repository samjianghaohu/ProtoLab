// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BehaviorConfig/IBCMeleeWeapon.h"
#include "Item/BehaviorConfig/ItemBehaviorDependencies.h"
#include "Item/Item.h"
#include "Character/ProlabCharacter.h"
#include "Character/PlayerInputHandler.h"
#include "Character/PlayerAnimInstance.h"
#include "Animation/AnimNotifyWithDelegates.h"
#include "EnhancedInputSubsystems.h"

#pragma region Config Initialization

UItemBehaviorRuntimeConfigBase* UIbcMeleeWeapon::InitializeRuntimeInternal()
{
	return NewObject<UIbcMeleeWeaponRuntime>();
}

#pragma endregion

#pragma region Runtime

void UIbcMeleeWeaponRuntime::CacheConfigFromConfigBase()
{
	Config = Cast<UIbcMeleeWeapon>(ConfigBase);

	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UIbcMeleeWeaponRuntime::Initialize - Config is null"));
		return;
	}

	auto HolderPlayer = Dependencies->GetItem()->GetHolderPlayer();
	if (HolderPlayer != nullptr)
	{
		PlayerController = Cast<APlayerController>(HolderPlayer->GetController());
	}
}

void UIbcMeleeWeaponRuntime::OnEnable()
{
	if (Config->MeleeWeaponInputMapping != nullptr && IsValid(PlayerController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Config->MeleeWeaponInputMapping, 2); // Make a priority enum for behavior inputs
		}
	}

	if (Config->IdleAnimation != nullptr)
	{
		Dependencies->GetPlayerAnimation()->AddIdleAnimOverride(Config->IdleAnimation);
	}

	bIsSwingAnimationPlaying = false;
}

void UIbcMeleeWeaponRuntime::Update()
{
	if (bIsSwingAnimationPlaying)
	{
		return;
	}

	auto InputValue = Dependencies->GetInputHandler()->GetInputActionValue(EPlayerInputType::EPIA_PrimaryAction);
	if (InputValue.Get<bool>())
	{
		bIsSwingAnimationPlaying = true;
		PlaySwingAnimation();
	}
}

void UIbcMeleeWeaponRuntime::Dispose()
{
	if (Config->IdleAnimation != nullptr)
	{
		Dependencies->GetPlayerAnimation()->RemoveIdleAnimaOverride();
	}

	if (Config->MeleeWeaponInputMapping != nullptr && IsValid(PlayerController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(Config->MeleeWeaponInputMapping);
		}
	}
}

void UIbcMeleeWeaponRuntime::PlaySwingAnimation()
{
	auto HolderPlayer = Dependencies->GetItem()->GetHolderPlayer();
	if (HolderPlayer != nullptr && Config->SwingAnimation != nullptr)
	{
		const TArray<FAnimNotifyEvent> NotifyEvents = Config->SwingAnimation->Notifies;
		if (NotifyEvents.Num() > 0)
		{
			if (const auto Notify = Cast<UAnimNotifyWithDelegates>(NotifyEvents[0].Notify))
			{
				Notify->OnNotified.AddUObject(this, &UIbcMeleeWeaponRuntime::OnSwingAnimationNotifyTriggered);
			}
		}

		HolderPlayer->PlayAnimMontage(Config->SwingAnimation, Config->SwingAnimationPlayRate);
	}
}

void UIbcMeleeWeaponRuntime::OnSwingAnimationNotifyTriggered()
{
	const TArray<FAnimNotifyEvent> NotifyEvents = Config->SwingAnimation->Notifies;
	if (NotifyEvents.Num() > 0)
	{
		if (const auto Notify = Cast<UAnimNotifyWithDelegates>(NotifyEvents[0].Notify))
		{
			Notify->OnNotified.RemoveAll(this);
		}
	}

	bIsSwingAnimationPlaying = false;
}

#pragma endregion
