// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyActorComponent.h"

// Sets default values for this component's properties
UDestroyActorComponent::UDestroyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDestroyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDestroyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	_DestoyDeltaTime -= DeltaTime;
	// ...

	if (_DestoyDeltaTime <= 0)
	{
		GetOwner()->Destroy();
	}
	else
	{
		PrimaryComponentTick.TickInterval = _DestoyDeltaTime;
	}
}

void UDestroyActorComponent::SetDestroyTime(float destroyTime)
{
	_DestoyDeltaTime = destroyTime;
}

