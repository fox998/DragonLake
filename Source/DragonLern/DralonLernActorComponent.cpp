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
	
	//if (GetOwner()->IsA<ADragonLernCharacter>())
	//{
	//	auto character = static_cast<ADragonLernCharacter>(GetOwner());
	//	character->GetController()->Is;

	//}
	//else
	//{
	//	ASSERT(false);
	//}
	//// ...
}


// Called when the game starts
void UDralonLernActorComponent::BeginPlay()
{

	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDralonLernActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("UDralonLernActorComponent::TickComponent")));
	// ...
}

