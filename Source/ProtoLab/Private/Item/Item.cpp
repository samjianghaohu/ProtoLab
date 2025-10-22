// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Character/ProlabCharacter.h"
#include "Character/PlayerBehaviorSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMeshComponent"));
	SetRootComponent(ItemMesh);
	RootMesh = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	InitializePhysicsAndCollision();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereOverlapEnd);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#pragma region IInteractable

bool AItem::CanInteract(AProlabCharacter* Player)
{
	if (Player == nullptr)
	{
		return false;
	}

	// Already holding an item
	if (Player->GetHeldItem() != nullptr)
	{
		return false;
	}

	return true;
}

void AItem::Interact(AProlabCharacter* Player)
{
	if (Player == nullptr)
	{
		return;
	}

	// Notify player and cache holder
	Player->SetHeldItem(this);
	SetHolderPlayerInternal(Player);
}

#pragma endregion

#pragma region Item Interface

bool AItem::CanBeDropped(AProlabCharacter* Player)
{
	if (Player == nullptr)
	{
		return false;
	}

	return Player->GetHeldItem() == this;
}

void AItem::Drop(AProlabCharacter* Player)
{
	if (Player == nullptr)
	{
		return;
	}

	// Notify player and clear holder
	SetHolderPlayerInternal(nullptr);
	Player->SetHeldItem(nullptr);
}

#pragma endregion


#pragma region Collisions

void AItem::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Overlapped with %s"), *OtherActor->GetName());

		auto ProlabCharacter = Cast<AProlabCharacter>(OtherActor);
		if (ProlabCharacter != nullptr)
		{
			ProlabCharacter->SetHoveredInteractable(this);
		}
	}
}

void AItem::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item End Overlapped with %s"), *OtherActor->GetName());

		auto ProlabCharacter = Cast<AProlabCharacter>(OtherActor);
		if (ProlabCharacter != nullptr)
		{
			if (ProlabCharacter->GetHoveredInteractable() == this)
			{
				ProlabCharacter->SetHoveredInteractable(nullptr);
			}
		}
	}
}

#pragma endregion

#pragma region Internal

void AItem::InitializePhysicsAndCollision()
{
	if (RootMesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Item %s: No valid root mesh. Cannot initialize Physics."), *GetName());
		return;
	}

	RootMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetEnableGravity(true);
}

void AItem::SetHolderPlayerInternal(AProlabCharacter* NewHolder)
{
	if (NewHolder == HolderPlayer)
	{
		// Holder didn't change. Do nothing.
		return;
	}

	if (HolderPlayer == nullptr)
	{
		// Holder is changing from null to a value. Item is picked up.
		HolderPlayer = NewHolder;
		OnPickup();
	}
	else if (NewHolder == nullptr)
	{
		// Holder is changing from a value to null. Item is released.
		OnRelease();
		HolderPlayer = NewHolder; // Set HolderPlayer to null AFTER runing OnRelease logic because some of that logic might still need information of the holder.
	}
	else
	{
		// NOTE: Add future cases such as passing on from one player to another.
	}
}

void AItem::OnPickup()
{
	// Disable physical collision and physics.
	if (RootMesh != nullptr)
	{
		RootMesh->SetSimulatePhysics(false);
		RootMesh->SetEnableGravity(false);

		RootMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// Attach to player
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	GetRootComponent()->AttachToComponent(HolderPlayer->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("HandGrip_R"));

	// Initialize item behavior.
	auto BehaviorSystem = HolderPlayer->GetBehaviorSystem();
	if (BehaviorSystem != nullptr)
	{
		BehaviorSystem->AddItemBehaviorConfig(this);
	}
}

void AItem::OnRelease()
{
	// Dispose item behavior
	auto BehaviorSystem = HolderPlayer->GetBehaviorSystem();
	if (BehaviorSystem != nullptr)
	{
		BehaviorSystem->RemoveItemBehaviorConfig(this);
	}

	// Detach from player
	GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	// Reenable physics and collision.
	RootMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetEnableGravity(true);
}

#pragma endregion
