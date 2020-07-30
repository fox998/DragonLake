// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Chaos/Array.h"
#include "PickableItemBuilder.h"
#include "PickupAIController.generated.h"

/**
 * 
 */
UCLASS()
class DRAGONLERN_API APickupAIController : public AAIController
{
	GENERATED_BODY()

public:
	APickupAIController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<ItemEfectType> _efectsToPick = {
		ItemEfectType::IncreaseSpeed,
		ItemEfectType::Jump,
		ItemEfectType::Heal
	};
};
