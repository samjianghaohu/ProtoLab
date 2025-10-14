// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProlabCharacter.generated.h"

class AItem;
class IInteractable;

UCLASS()
class PROTOLAB_API AProlabCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProlabCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Setters and Getters
	FORCEINLINE class UPlayerInputHandler* GetInputHandler() const { return PlayerInputHandler; }
	// TODO: extract this to a dedicated interaction targeting system
	FORCEINLINE void SetHoveredInteractable(IInteractable* Interactable) { HoveredInteractable = Interactable; }
	FORCEINLINE IInteractable* GetHoveredInteractable() const { return HoveredInteractable; }
	FORCEINLINE void SetHeldItem(AItem* NewItem) { HeldItem = NewItem; }
	FORCEINLINE AItem* GetHeldItem() const { return HeldItem; }
#pragma endregion

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* LocoMappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category = Behavior)
	TArray<class UPlayerBehaviorConfigBase*> AlwaysActiveBehaviorConfigs; // TODO: make this into a data asset

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* ViewCamera = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPlayerLocomotion* PlayerLocomotion = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPlayerBehaviorSystem* PlayerBehaviorSystem = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UPlayerInputHandler* PlayerInputHandler = nullptr;

#pragma endregion

	// TODO: extract this to a dedicated interaction targeting system
	IInteractable* HoveredInteractable = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Interaction)
	AItem* HeldItem = nullptr;

};
