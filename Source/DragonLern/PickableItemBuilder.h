// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PickableItem.h"
#include "PickableItemBuilder.generated.h"


UENUM()
enum ItemEfectType
{
	Heal,
	Damage,
	Speed,
	COUNT
};

/**
 * 
 */
UCLASS(ClassGroup = (Custom), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class DRAGONLERN_API UPickableItemBuilder : public UObject
{
	GENERATED_BODY()

public:
	
	UPickableItemBuilder() {}

	static void AsamblePickableItem(APickableItem* asablingBase, ItemEfectType);
	static ItemEfectType GetRandomEfect();

	static UPickableItemBuilder const& GetInstance();

	UPROPERTY(EditDefaultsOnly)
	int32 DamageEfect = 20;

	UPROPERTY(EditDefaultsOnly)
	int32 HealEfect = 20;

};
