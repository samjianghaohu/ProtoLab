// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/MeleeWeapon.h"
#include "Character/ProlabCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AMeleeWeapon::AMeleeWeapon()
{
	WeaponHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponHitBox"));
	WeaponHitBox->SetupAttachment(GetRootComponent());
	WeaponHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceStart"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("BoxTraceEnd"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AMeleeWeapon::StartSwinging()
{
	bIsSwinging = true;
}

void AMeleeWeapon::EndSwinging()
{
	bIsSwinging = false;
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	WeaponHitBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnHitBoxOverlapBegin);

	bIsSwinging = false;
}

void AMeleeWeapon::OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsSwinging)
	{
		return;
	}

	if (OtherActor == nullptr || OtherActor == this)
	{
		return;
	}

	if (AProlabCharacter* HitCharacter = Cast<AProlabCharacter>(OtherActor))
	{
		// Don't hit the wielder
		if (HitCharacter == GetHolderPlayer())
		{
			return;
		}
	}

	BoxTraceAlongHitBox();
}

FHitResult AMeleeWeapon::BoxTraceAlongHitBox()
{
	const FVector TraceStart = BoxTraceStart->GetComponentLocation();
	const FVector TraceEnd = BoxTraceEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Emplace(this);

	FHitResult BoxTraceHit;

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		TraceStart,
		TraceEnd,
		FVector(5.f, 5.f, 5.f),
		BoxTraceStart->GetComponentRotation(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		BoxTraceHit,
		true
	);

	return BoxTraceHit;
}
