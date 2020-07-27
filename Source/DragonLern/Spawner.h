// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PickableItem.h"
#include "Spawner.generated.h"

UCLASS()
class DRAGONLERN_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector getItemLocation();

	UPROPERTY(EditAnywhere)
	UBoxComponent* _box;

	UPROPERTY(EditAnywhere)
	int32 _itemSpawnDelta = 2;

	UPROPERTY(EditAnywhere)
	int32 _itemMaxNumber = 2;

	UPROPERTY(EditAnywhere)
	int32 _itemMinDistance = 500;

	UPROPERTY(EditAnywhere)
	int32 _itemLifeTime = 2;

private:
	UPROPERTY()
	TArray<APickableItem*> _items;

};
