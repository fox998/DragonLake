// Fill out your copyright notice in the Description page of Project Settings.


#include "PeckableCounterComponent.h"
#include "PickableItem.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UPeckableCounterComponent::UPeckableCounterComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPeckableCounterComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* pickable = Cast<ACharacter>(GetOwner());
	if (pickable)
	{
		pickable->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &UPeckableCounterComponent::OnBeginCapsuleOverlap);
	}	
}

void UPeckableCounterComponent::OnBeginCapsuleOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	auto const* const item = Cast<APickableItem>(OtherActor);
	if (item)
	{
		ProcessOverlapWithPeckable(item);
	}
}


void UPeckableCounterComponent::ProcessOverlapWithPeckable(APickableItem const* item)
{
	PickableEfectBase::EfectTypeT const efectType = item->GetEfect()->GetEfectType();
	uint32* const counterPtr = _ItemsTypeCounts.Find(efectType);
	if (counterPtr)
	{
		++(*counterPtr);
	}
	else
	{
		_ItemsTypeCounts.Emplace(efectType, 1);
	}

	auto debugText = FString::Printf(TEXT("Items of type %d was picked : %d"), (int32)efectType, _ItemsTypeCounts[efectType]);
		GEngine->AddOnScreenDebugMessage(
		(int32)efectType,
		5,
		item->GetColor(),
		debugText
	);
}

// Called every frame
void UPeckableCounterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

