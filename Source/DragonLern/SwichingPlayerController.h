// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SwichingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DRAGONLERN_API ASwichingPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASwichingPlayerController();

	virtual void SetupInputComponent() override;
	void SwitchCharacter();

};
