// Copyright Epic Games, Inc. All Rights Reserved.

#include "DragonLernGameMode.h"
#include "DragonLernCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerState.h"

ADragonLernGameMode::ADragonLernGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	//MyPlayerState: No file on disk
}
