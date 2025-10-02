// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerLocomotion.generated.h"

class UInputAction;
struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOLAB_API UPlayerLocomotion : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerLocomotion();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

protected:
	virtual void BeginPlay() override;

#pragma region Input

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAroundAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction = nullptr;

#pragma endregion

private:
	UPROPERTY(VisibleAnywhere)
	ACharacter* Player = nullptr;

#pragma region Input Callbacks

	void Move(const FInputActionValue& Value);

	void LookAround(const FInputActionValue& Value);

	void Jump();

#pragma endregion
};
