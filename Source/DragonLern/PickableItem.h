// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "PickableItem.generated.h"


struct OverlapParams
{
	UPrimitiveComponent* OverlappedComponent;
	AActor* OtherActor;
	UPrimitiveComponent* OtherComp;
	int32 OtherBodyIndex;
	bool bFromSweep;
	const FHitResult& SweepResul;
};


struct PickableEfectBase
{
	virtual void ApplyEfect(OverlapParams const&) {};
};


UCLASS()
class DRAGONLERN_API APickableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	
	using EfectContainer = PickableEfectBase*;

	void SetLifetime(float time) { _lifeTime = time; }
	void SetEfect(EfectContainer newEfect) { _itemEfect = std::move(newEfect); }
	void SetColor(FColor newColor);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* _meshComponent;
	
	UPROPERTY(EditAnywhere)
	USphereComponent* _sphereComponent;


private:
	EfectContainer _itemEfect;
	float _lifeTime;
	UMaterialInstanceDynamic* _dynamicMaterial;

};
