// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "GenericPlatform/GenericPlatformMath.h"
//#include "../Plugins/Experimental/GeometryProcessing/Source/GeometricObjects/Public/MathUtil.h"

// Sets default values for this component's properties
UBuffComponent::UBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UBuffComponent::IncriaseBuffTime(float upTime)
{
	if (_efectTime <= 0)
	{
		//PrimaryComponentTick.SetTickFunctionEnable(true);
		OnActivateEfect();
	}
	_efectTime = FGenericPlatformMath::Max<float>(0.f, _efectTime) +  upTime;
}

// Called when the game starts
void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (_efectTime > 0)
	{
		_efectTime -= DeltaTime;

		if (_efectTime <= 0)
		{
			//PrimaryComponentTick.SetTickFunctionEnable(false);
			OnDeactivateEfect();
		}
	}
	// ...
}

