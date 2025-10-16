// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BehaviorConfig/ItemBehaviorDependencies.h"

void UItemBehaviorDependencies::Initialize(AItem* InItem, UPlayerInputHandler* InInputHandler)
{
	Item = InItem;
	InputHandler = InInputHandler;
}
