// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class DRAGONLERN_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PerformanceTest();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int mLoopIterationCount = 1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float mLineEnd = 1000;

};
