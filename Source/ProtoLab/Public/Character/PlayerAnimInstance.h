// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * Defines custom behavior of player animation and exposes relevant properties.
 */
UCLASS()
class PROTOLAB_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bJumpUpFromGround;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Animation Override")
	bool bHasIdleAnimOverride = false;

	UPROPERTY(BlueprintReadOnly, Category = "Animation Override")
	class UAnimSequence* IdleAnimOverride = nullptr;

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void AddIdleAnimOverride(UAnimSequence* AnimOverride);

	void RemoveIdleAnimaOverride();

private:
	UPROPERTY(VisibleAnywhere)
	class ACharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementComponent* CharacterMovementComponent;
};
