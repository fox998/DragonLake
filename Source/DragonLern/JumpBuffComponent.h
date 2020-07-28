// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "JumpBuffComponent.generated.h"

/**
 * 
 */
UCLASS()
class DRAGONLERN_API UJumpBuffComponent : public UBuffComponent
{
	GENERATED_BODY()
public:
	virtual void OnActivateEfect() override;
	virtual void OnDeactivateEfect() override;

	void ChengeJumpHeight(float deltaSpeed);

	UPROPERTY()
	float _JumpDelta = 2;
};
