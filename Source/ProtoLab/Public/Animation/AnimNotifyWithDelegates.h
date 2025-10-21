// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyWithDelegates.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNotifiedSignature)

/**
 * A variant of AnimNotify that broadcasts events that other C++ classes can subscribe to
 */
UCLASS()
class PROTOLAB_API UAnimNotifyWithDelegates : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnNotifiedSignature OnNotified;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
