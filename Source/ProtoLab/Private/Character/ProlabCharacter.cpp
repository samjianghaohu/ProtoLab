// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProlabCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/PlayerLocomotion.h"

AProlabCharacter::AProlabCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create camera related components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->bUsePawnControlRotation = true;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);

	// Create player related components
	PlayerLocomotion = CreateDefaultSubobject<UPlayerLocomotion>(TEXT("PlayerLocomotion"));
}

void AProlabCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProlabCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProlabCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

