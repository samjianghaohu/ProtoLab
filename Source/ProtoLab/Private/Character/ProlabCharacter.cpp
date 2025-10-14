// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/ProlabCharacter.h"
#include "Camera/CameraComponent.h"
#include "Character/BehaviorConfig/PlayerBehaviorConfigBase.h"
#include "Character/PlayerBehaviorSystem.h"
#include "Character/PlayerInputHandler.h"
#include "Character/PlayerLocomotion.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"

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
	// TODO: move these to a local player controller component or something
	PlayerInputHandler = CreateDefaultSubobject<UPlayerInputHandler>(TEXT("PlayerInputHandler"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AProlabCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(LocoMappingContext, 0);
		}
	}

	// TODO: move these to a local player controller component or something
	PlayerBehaviorSystem = NewObject<UPlayerBehaviorSystem>(this, UPlayerBehaviorSystem::StaticClass());
	if (PlayerBehaviorSystem != nullptr)
	{
		PlayerBehaviorSystem->Initialize(this);

		for (UPlayerBehaviorConfigBase* Config : AlwaysActiveBehaviorConfigs)
		{
			if (Config != nullptr)
			{
				PlayerBehaviorSystem->AddBehaviorConfig(Config);
			}
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

	if (PlayerInputHandler != nullptr)
	{
		PlayerInputHandler->SetupPlayerInputComponent(PlayerInputComponent);
	}
}

