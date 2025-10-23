// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ItemInteractionSettings.h"
#include "Item.generated.h"

class AProlabCharacter;
class UItemBehaviorConfigBase;
class UItemBehaviorRuntimeConfigBase;

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
	void Drop(const FVector InReleaseDirection = FVector::ZeroVector, const float InReleaseSpeed = 0.0f);

	FORCEINLINE UItemBehaviorConfigBase* GetItemBehaviorConfig() const { return InteractionSettings.ItemBehaviorConfig; }
	FORCEINLINE void CacheRuntimeBehavior(UItemBehaviorRuntimeConfigBase* RuntimeBehavior) { CachedRuntimeBehavior = RuntimeBehavior; }
	FORCEINLINE UItemBehaviorRuntimeConfigBase* GetCachedRuntimeBehavior() const { return CachedRuntimeBehavior; }
	FORCEINLINE AProlabCharacter* GetHolderPlayer() const { return HolderPlayer; }
#pragma endregion


protected:
	UPROPERTY(EditAnywhere, Category = Interaction)
	FItemInteractionSettings InteractionSettings;

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

	UStaticMeshComponent* RootMesh = nullptr;
	
	UItemBehaviorRuntimeConfigBase* CachedRuntimeBehavior = nullptr;

	/// <summary>
	/// DO NOT directly set this variable. Do it via SetHolderPlayerInternal instead.
	/// </summary>
	AProlabCharacter* HolderPlayer = nullptr;

	FVector ReleaseDirection = FVector::ZeroVector;

	float ReleaseSpeed = 0.0f;

#pragma region Internal
	void InitializePhysicsAndCollision();
	void SetHolderPlayerInternal(AProlabCharacter* NewHolder);
	void OnPickup();
	void OnRelease();
#pragma endregion

};
