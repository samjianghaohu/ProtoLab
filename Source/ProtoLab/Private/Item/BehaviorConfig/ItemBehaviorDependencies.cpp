// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BehaviorConfig/ItemBehaviorDependencies.h"
#include "Character/ProlabCharacter.h"
#include "Character/PlayerAnimInstance.h"

void UItemBehaviorDependencies::Initialize(AItem* InItem, AProlabCharacter* LocalPlayer)
{
	Item = InItem;

	if (LocalPlayer != nullptr)
	{
		InputHandler = LocalPlayer->GetInputHandler();

		auto PlayerMesh = LocalPlayer->GetMesh();
		if (PlayerMesh != nullptr)
		{
			PlayerAnimation = Cast<UPlayerAnimInstance>(PlayerMesh->GetAnimInstance());
		}
	}
}
