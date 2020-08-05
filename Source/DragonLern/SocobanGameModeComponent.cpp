// Fill out your copyright notice in the Description page of Project Settings.


#include "SocobanGameModeComponent.h"

// Sets default values for this component's properties
USocobanGameModeComponent::USocobanGameModeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USocobanGameModeComponent::BeginPlay()
{
	Super::BeginPlay();
	ResetGoals();
	// ...
	
}


// Called every frame
void USocobanGameModeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	_IsReseted = false;
	// ...
}

void USocobanGameModeComponent::ResetGoals()
{
	if (!_IsReseted)
	{
		_GoalsCounter = 0;
		_IsReseted = true;
	}
}

void USocobanGameModeComponent::IncreaseGoals()
{
	_GoalsCounter++;
}

void USocobanGameModeComponent::DecreaseGoals()
{
	_GoalsCounter--;

	if (_GoalsCounter <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("YOU WIN!!")));
	}
}

