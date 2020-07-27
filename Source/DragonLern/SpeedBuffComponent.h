// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "SpeedBuffComponent.generated.h"

/**
 * 
 */
UCLASS()
class DRAGONLERN_API USpeedBuffComponent : public UBuffComponent
{
	GENERATED_BODY()
public:
	USpeedBuffComponent();
	virtual void OnActivateEfect() override;
	virtual void OnDeactivateEfect() override;
	
	void ChengeSpeed(float deltaSpeed);

	UPROPERTY()
	float _SpeedDelta = 5;
};
