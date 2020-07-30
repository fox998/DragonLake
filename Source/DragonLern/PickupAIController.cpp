// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupAIController.h"
#include "EngineUtils.h"
#include "PickableItem.h"

APickupAIController::APickupAIController()
{
}

void APickupAIController::BeginPlay()
{
	Super::BeginPlay();
}

void APickupAIController::Tick(float DeltaTime)
{
	for (TActorIterator<APickableItem> pikableIt(GetWorld()); pikableIt; ++pikableIt)
	{
		APickableItem* item = *pikableIt;
		APickableItem::EfectContainer const& efect = item->GetEfect();
		ItemEfectType efectType = (efect ? (ItemEfectType)efect->GetEfectType() : ItemEfectType::COUNT);

		if (!item->IsHidden() && _efectsToPick.Find(efectType) != INDEX_NONE)
		{
			MoveToActor(*pikableIt);
			break;
		}
	}
}
