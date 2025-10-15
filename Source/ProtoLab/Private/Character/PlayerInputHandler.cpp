// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInputHandler.h"
#include "PlayerInput/PlayerInputConfig.h"
#include "EnhancedInputComponent.h"

UPlayerInputHandler::UPlayerInputHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInputHandler::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerInputHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerInputHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PopulateInputActionMap(PlayerInputComponent);
}

void UPlayerInputHandler::PopulateInputActionMap(UInputComponent* PlayerInputComponent)
{
	InputActionMap.Empty();

	CachedEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (CachedEnhancedInputComponent != nullptr)
	{
		if (InputConfigs != nullptr)
		{
			for (FPlayerInputConfig Config : InputConfigs->PlayerInputConfigs)
			{
				if (Config.InputType != EPlayerInputType::EPIA_None && Config.InputAction != nullptr)
				{
					CachedEnhancedInputComponent->BindActionValue(Config.InputAction);
					InputActionMap.Emplace(Config.InputType, Config.InputAction);
				}
			}
		}
	}
}

FInputActionValue UPlayerInputHandler::GetInputActionValue(EPlayerInputType InputType)
{
	if (InputType == EPlayerInputType::EPIA_None)
	{
		UE_LOG(LogTemp, Warning, TEXT("Getting input action value for type None is invalid! Check your code."));
		return FInputActionValue();
	}

	if (CachedEnhancedInputComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enhanced input component is not cached! Did you call SetupPlayerInputComponent?"));
		return FInputActionValue();
	}

	auto ActionPtr = InputActionMap.Find(InputType);
	if (ActionPtr != nullptr && *ActionPtr != nullptr)
	{
		return CachedEnhancedInputComponent->GetBoundActionValue(*ActionPtr);
	}

	UE_LOG(LogTemp, Warning, TEXT("No input action mapped for input type %d. Did you set it up correctly?"), static_cast<uint8>(InputType));
	return FInputActionValue();
}

