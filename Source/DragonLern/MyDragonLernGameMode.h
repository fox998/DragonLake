// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DragonLernGameMode.h"
#include "MyPlayerState.h"
#include "MyDragonLernGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DRAGONLERN_API AMyDragonLernGameMode : public ADragonLernGameMode
{
	GENERATED_BODY()
public:
	AMyDragonLernGameMode()
	{
		static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacterD"));
		if (PlayerPawnBPClass.Class != NULL)
		{
			DefaultPawnClass = PlayerPawnBPClass.Class;
		}
		PlayerStateClass = TSubclassOf<AMyPlayerState>();
	}
};
