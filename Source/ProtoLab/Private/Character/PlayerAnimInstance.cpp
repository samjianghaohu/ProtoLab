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