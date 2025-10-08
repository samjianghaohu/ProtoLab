// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ProlabCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/PlayerLocomotion.h"
#include "EnhancedInputSubsystems.h"
#include "Character/PlayerBehaviorSystem.h"

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
	PlayerBehaviorSystem = CreateDefaultSubobject<UPlayerBehaviorSystem>(TEXT("PlayerBehaviorSystem"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AProlabCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}
	}

	if (PlayerBehaviorSystem != nullptr)
	{
		PlayerBehaviorSystem->Initialize();

		if (InteractWithInteractableConfig != nullptr)
		{
			PlayerBehaviorSystem->AddBehaviorConfig(InteractWithInteractableConfig);
		}
	}
}

void AProlabCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerBehaviorSystem != nullptr)
	{
		PlayerBehaviorSystem->Update(DeltaTime);
	}
}

void AProlabCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Locomotion related input are handled by PlayerLocomotion component
	if (PlayerLocomotion != nullptr)
	{
		PlayerLocomotion->SetupPlayerInputComponent(PlayerInputComponent);
	}
}

