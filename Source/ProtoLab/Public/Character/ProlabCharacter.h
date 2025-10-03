// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProlabCharacter.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* CharacterMappingContext = nullptr;

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* ViewCamera = nullptr;

	UPROPERTY(VisibleAnywhere)
	UPlayerLocomotion* PlayerLocomotion = nullptr;

#pragma endregion

};
