// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <deque>

#include "ActorsTracker.generated.h"

class APlayerController;

UCLASS()
class DRAGONLERN_API AActorsTracker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorsTracker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SelectActorUnderCursor();
	UFUNCTION()
	void DisplayAllActorsBetweenSelected();
	UFUNCTION()
	void LogAllActorsInViewport();

	UPROPERTY(EditAnywhere)
	APlayerController* _PlayerController;

	UPROPERTY(EditAnywhere)
	float _TraceVectorLength = 10000;

private:

	std::deque<AActor*> _SelectedActors;
};
