// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Item.generated.h"

class AProlabCharacter;

UCLASS()
class PROTOLAB_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AItem();

	virtual void Tick(float DeltaTime) override;

#pragma region IInteractable
	virtual bool CanInteract(AProlabCharacter* Player) override;
	virtual void Interact(AProlabCharacter* Player) override;
#pragma endregion

#pragma region Item Interface
	virtual bool CanBeDropped(AProlabCharacter* Player);
	void Drop(AProlabCharacter* Player);
#pragma endregion


protected:
	virtual void BeginPlay() override;

#pragma region Collisions

	UFUNCTION()
	virtual void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

#pragma endregion

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere = nullptr;
};
