// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProlabCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROTOLAB_API AProlabCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProlabCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
#pragma region MyRegion

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera = nullptr;

#pragma endregion

};
