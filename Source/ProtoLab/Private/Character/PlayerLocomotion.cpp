// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerLocomotion.h"
#include "Character/PlayerInputHandler.h"
#include "Character/ProlabCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UPlayerLocomotion::UPlayerLocomotion()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerLocomotion::BeginPlay()
{
	Super::BeginPlay();

	// Cache player, and configure a bunch of properties.
	// Do this in BeginPlay to ensure the owner is fully initialized.
	Player = Cast<ACharacter>(GetOwner());
	if (Player != nullptr)
	{
		Player->bUseControllerRotationPitch = false;
		Player->bUseControllerRotationRoll = false;
		Player->bUseControllerRotationYaw = false;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerLocomotion: Owner is not a Character!"));
	}

	UCharacterMovementComponent* MovementComponent = Player != nullptr ? Player->GetCharacterMovement() : nullptr;
	if (MovementComponent != nullptr)
	{
		MovementComponent->bOrientRotationToMovement = true;
	}

	// Cache input handler to access input values.
	auto ProlabCharacter = Cast<AProlabCharacter>(GetOwner());
	if (ProlabCharacter != nullptr)
	{
		InputHandler = ProlabCharacter->GetInputHandler();
	}
}

void UPlayerLocomotion::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateMovement(DeltaTime);
}

#pragma region Movement

void UPlayerLocomotion::UpdateMovement(float DeltaTime)
{
	if (InputHandler == nullptr) return;

	// First, resolve jump
	if (InputHandler->GetJumpActionValue().Get<bool>())
	{
		Jump();
	}

	// Then, resolve camera looking around
	LookAround(InputHandler->GetLookAroundActionValue());

	// Last, resolve movement
	Move(InputHandler->GetMoveActionValue());
}

void UPlayerLocomotion::Move(const FInputActionValue& Value)
{
	if (Player == nullptr) return;

	auto InputVector = Value.Get<FVector2D>();
	if (!InputVector.IsNearlyZero())
	{
		const FRotator ControllerRot = Player->GetControlRotation();
		const FRotator ControllerYaw = FRotator(0.0f, ControllerRot.Yaw, 0.0f);

		FVector CurrentTargetForward = FRotationMatrix(ControllerYaw).GetUnitAxis(EAxis::X);
		FVector CurrentTargetRight = FRotationMatrix(ControllerYaw).GetUnitAxis(EAxis::Y);

		Player->AddMovementInput(CurrentTargetForward, InputVector.Y);
		Player->AddMovementInput(CurrentTargetRight, InputVector.X);
	}
}

void UPlayerLocomotion::LookAround(const FInputActionValue& Value)
{
	if (Player == nullptr) return;

	auto LookAxisVector = Value.Get<FVector2D>();
	if (!LookAxisVector.IsNearlyZero())
	{
		Player->AddControllerYawInput(LookAxisVector.X);
		Player->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void UPlayerLocomotion::Jump()
{
	if (Player == nullptr) return;

	Player->Jump();
}

#pragma endregion

