// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProlabCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPlayerLocomotion;

UCLASS()
class PROTOLAB_API AProlabCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProlabCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPlayerLocomotion* PlayerLocomotion = nullptr;

#pragma endregion

};
