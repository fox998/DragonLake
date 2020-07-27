// Fill out your copyright notice in the Description page of Project Settings.


#include "DralonLernActorComponent.h"
#include "DragonLernCharacter.h"

// Sets default values for this component's properties
UDralonLernActorComponent::UDralonLernActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = _damageFrequency;
}


void UDralonLernActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	_dragonLernCharacterOwner = nullptr;
}

// Called when the game starts
void UDralonLernActorComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->IsA<ADragonLernCharacter>())
	{
		_dragonLernCharacterOwner = Cast<ADragonLernCharacter>(GetOwner());
	}	
}


// Called every frame
void UDralonLernActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (_dragonLernCharacterOwner)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Green, FString::Printf(TEXT("UDralonLernActorComponent::TickComponent do damage")));
		_dragonLernCharacterOwner->HPDeltaChange(-_damage);
	}
}

