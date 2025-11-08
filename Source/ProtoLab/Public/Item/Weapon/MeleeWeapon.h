// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "MeleeWeapon.generated.h"

class UBoxComponent;

/**
 * Shared class for all melee weapons
 */
UCLASS()
class PROTOLAB_API AMeleeWeapon : public AItem
{
	GENERATED_BODY()

public:
	AMeleeWeapon();

	void StartSwinging();

	void EndSwinging();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	UBoxComponent* WeaponHitBox = nullptr;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart = nullptr;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd = nullptr;

	FHitResult BoxTraceAlongHitBox();

	bool bIsSwinging = false;
};
