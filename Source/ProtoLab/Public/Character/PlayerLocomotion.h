// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerLocomotion.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOLAB_API UPlayerLocomotion : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerLocomotion();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	ACharacter* Player = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPlayerInputHandler* Input = nullptr;

#pragma region Movement

	void UpdateMovement(float DeltaTime);

	void Move(const FInputActionValue& Value);

	void LookAround(const FInputActionValue& Value);

	void Jump();

#pragma endregion
};
