// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridSnapedActor.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;

UCLASS(BlueprintType)
class DRAGONLERN_API AGridSnapedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridSnapedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* _meshComponent;

	UPROPERTY(EditAnywhere)
	uint32 _GridSize = 100;
	
	UPROPERTY(EditAnywhere)
	float _ShiftFromBound = 0.1;
private:

	bool IsValidPlayerPosition(AActor* otherActor, FVector actorBox) const;

	bool _IsTicked = false;
};
