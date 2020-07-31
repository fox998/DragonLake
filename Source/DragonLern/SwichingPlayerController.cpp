// Fill out your copyright notice in the Description page of Project Settings.


#include "SwichingPlayerController.h"
#include "DragonLernCharacter.h"
#include "EngineUtils.h"

ASwichingPlayerController::ASwichingPlayerController()
{
}

void ASwichingPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Switch", IE_Pressed, this, &ASwichingPlayerController::SwitchCharacter);
}

void ASwichingPlayerController::SwitchCharacter()
{
	for (TActorIterator<ADragonLernCharacter> characterIt(GetWorld()); characterIt; ++characterIt)
	{
		auto* currentPawn = GetPawn<ADragonLernCharacter>();
		if (*characterIt != currentPawn)
		{
			UnPossess();
			Possess(*characterIt);
			break;
		}
	}
}
