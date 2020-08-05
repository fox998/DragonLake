// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "SocobanGoalActor.generated.h"

class USocobanGameModeComponent;

UCLASS()
class DRAGONLERN_API ASocobanGoalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASocobanGoalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnActorBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);

	UFUNCTION()
		void OnActorEndOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

private:


	USocobanGameModeComponent* GetSocobanGameModeComponent() const;

	UPROPERTY(EditAnywhere)
		UPointLightComponent* _light;

	UPROPERTY(EditAnywhere)
		UBoxComponent* _box;

};
