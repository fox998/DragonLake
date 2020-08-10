// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroebleActorsSpawner.generated.h"

class USphereComponent;

USTRUCT()
struct FSpawneedObjectParams
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UStaticMesh* _Mesh;
	
	UPROPERTY(EditAnywhere)
	float _LifeTime;
};

UCLASS()
class DRAGONLERN_API ADestroebleActorsSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroebleActorsSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	AActor* GetNewActor() const;

	UPROPERTY(EditAnywhere)
	TArray<FSpawneedObjectParams> _SpawnetOpbjectsParams;

	UPROPERTY(EditAnywhere)
	USphereComponent* _Sphere;

	UPROPERTY(EditAnywhere)
	float _ItemMinDistance = 100;

	UPROPERTY(EditDefaultsOnly)
	float _DestroyComponentActivationTimeFromGameStart = 10;
};
