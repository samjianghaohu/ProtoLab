// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	PlayerCharacter = Cast<ACharacter>(TryGetPawnOwner());
	if (PlayerCharacter != nullptr)
	{
		CharacterMovementComponent = PlayerCharacter->GetCharacterMovement();
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (PlayerCharacter != nullptr && CharacterMovementComponent != nullptr)
	{
		bJumpUpFromGround = PlayerCharacter->JumpCurrentCount > 0 && !PlayerCharacter->bWasJumping;
		bIsFalling = CharacterMovementComponent->IsFalling();

		auto PlayerVelocityWs = CharacterMovementComponent->Velocity;
		auto PlayerUp = PlayerCharacter->GetActorUpVector();
		auto ProjectedVelocityWs = FVector::VectorPlaneProject(PlayerVelocityWs, PlayerUp);
		GroundSpeed = ProjectedVelocityWs.Size();
	}
}

// TODO: Consider making this into a prioritized token map so that multiple systems can use it at the same time
void UPlayerAnimInstance::AddIdleAnimOverride(UAnimSequence* AnimOverride)
{
	IdleAnimOverride = AnimOverride;
	bHasIdleAnimOverride = IsValid(IdleAnimOverride);
}

void UPlayerAnimInstance::RemoveIdleAnimaOverride()
{
	bHasIdleAnimOverride = false;
	IdleAnimOverride = nullptr; // TODO: Wait until blend out is finished before removing override anim reference.
}