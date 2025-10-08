// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Components/StaticMeshComponent.h"
#include <Components/SphereComponent.h>
#include "Character/ProlabCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	SetRootComponent(ItemMesh);

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

void AItem::Interact()
{
}

#pragma region Collisions

void AItem::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item Overlapped with %s"), *OtherActor->GetName());

		auto ProlabCharacter = Cast<AProlabCharacter>(OtherActor);
		if (ProlabCharacter != nullptr)
		{
			ProlabCharacter->SetHoveredItem(this);
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
			if (ProlabCharacter->GetHoveredItem() == this)
			{
				ProlabCharacter->SetHoveredItem(nullptr);
			}
		}
	}
}

#pragma endregion