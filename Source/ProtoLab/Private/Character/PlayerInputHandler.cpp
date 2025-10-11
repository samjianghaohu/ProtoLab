// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerInputHandler.h"

UPlayerInputHandler::UPlayerInputHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerInputHandler::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerInputHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerInputHandler::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			MoveActionBinding = &EnhancedInputComponent->BindActionValue(MoveAction);
		}
		if (LookAroundAction)
		{
			LookAroundActionBinding = &EnhancedInputComponent->BindActionValue(LookAroundAction);
		}
		if (JumpAction)
		{
			JumpActionBinding = &EnhancedInputComponent->BindActionValue(JumpAction);
		}
		if (InteractAction)
		{
			InteractActionBinding = &EnhancedInputComponent->BindActionValue(InteractAction);
		}
		if (DropAction)
		{
			DropActionBinding = &EnhancedInputComponent->BindActionValue(DropAction);
		}
	}
}

