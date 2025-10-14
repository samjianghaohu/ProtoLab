// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputComponent.h"
#include "PlayerInputHandler.generated.h"

class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOLAB_API UPlayerInputHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerInputHandler();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

#pragma region Input Action Value Getters
	// TODO: make this into one function with an enum param?
	FORCEINLINE FInputActionValue GetMoveActionValue() const { return MoveActionBinding != nullptr ? MoveActionBinding->GetValue() : FInputActionValue(); }
	FORCEINLINE FInputActionValue GetLookAroundActionValue() const { return LookAroundActionBinding != nullptr ? LookAroundActionBinding->GetValue() : FInputActionValue(); }
	FORCEINLINE FInputActionValue GetJumpActionValue() const { return JumpActionBinding != nullptr ? JumpActionBinding->GetValue() : FInputActionValue(); }
	FORCEINLINE FInputActionValue GetInteractActionValue() const { return InteractActionBinding != nullptr ? InteractActionBinding->GetValue() : FInputActionValue(); }
	FORCEINLINE FInputActionValue GetDropActionValue() const { return DropActionBinding != nullptr ? DropActionBinding->GetValue() : FInputActionValue(); }
#pragma endregion

protected:
	virtual void BeginPlay() override;

#pragma region Input Actions
	// TODO: Store these in an asset and just reference the asset here
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAroundAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* DropAction = nullptr;

#pragma endregion

private:
#pragma region Action Bindings
	// Store bindings to query action values later
	// TODO: store them in an array or something so we can access them with an enum/index
	FEnhancedInputActionValueBinding* MoveActionBinding;
	FEnhancedInputActionValueBinding* LookAroundActionBinding;
	FEnhancedInputActionValueBinding* JumpActionBinding;
	FEnhancedInputActionValueBinding* InteractActionBinding;
	FEnhancedInputActionValueBinding* DropActionBinding;
#pragma endregion
};
