// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Components/StaticMeshComponent.h"
#include <Components/SphereComponent.h>
#include "Character/ProlabCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetRootComponent() == nullptr)
	{
		SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot")));
	}

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetupAttachment(GetRootComponent());

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
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

	// Notify player
	Player->SetHeldItem(this);

	// Attach to player
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	GetRootComponent()->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("HandGrip_R"));
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