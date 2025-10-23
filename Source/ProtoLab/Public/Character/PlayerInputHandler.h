// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerInput/PlayerInputTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInputHandler.generated.h"

class UInputAction;
class UInputComponent;
struct FInputActionValue;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOLAB_API UPlayerInputHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerInputHandler();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	FInputActionValue GetInputActionValue(EPlayerInputType InputType);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UPlayerInputConfigs* InputConfigs = nullptr;

private:
	UPROPERTY()
	class UEnhancedInputComponent* CachedEnhancedInputComponent = nullptr;

	// Keeps track of the correspondence of Input type enum and the actual input action,
	// so that player logic can just request input value with the enum.
	TMap<EPlayerInputType, UInputAction*> InputActionMap;

	void PopulateInputActionMap(UInputComponent* PlayerInputComponent);
};
