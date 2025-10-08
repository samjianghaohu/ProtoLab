// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProlabCharacter.generated.h"

class AItem;

UCLASS()
class PROTOLAB_API AProlabCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProlabCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetHoveredItem(AItem* Item) { HoveredItem = Item; }

	FORCEINLINE AItem* GetHoveredItem() const { return HoveredItem; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* CharacterMappingContext = nullptr;

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UPlayerBehaviorConfigBase* InteractWithInteractableConfig = nullptr;

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

#pragma endregion

	UPROPERTY(VisibleInstanceOnly)
	AItem* HoveredItem = nullptr;

};
