#pragma once

#include "CoreMinimal.h"
#include "PlayerInputTypes.generated.h"

UENUM(BlueprintType)
enum class EPlayerInputType : uint8
{
	EPIA_None = 0 UMETA(DisplayName = "NONE"),
	EPIA_Move UMETA(DisplayName = "Move"),
	EPIA_LookAround UMETA(DisplayName = "Look Around"),
	EPIA_Jump UMETA(DisplayName = "Jump"),
	EPIA_Interact UMETA(DisplayName = "Interact"),
	EPIA_Drop UMETA(DisplayName = "Drop"),
	EPIA_PrimaryAction UMETA(DisplayName = "Primary Action")
};

USTRUCT(BlueprintType)
struct FPlayerInputConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayerInputType InputType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UInputAction* InputAction;
};