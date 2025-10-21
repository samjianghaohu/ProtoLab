// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifyWithDelegates.h"

void UAnimNotifyWithDelegates::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	OnNotified.Broadcast();
}
