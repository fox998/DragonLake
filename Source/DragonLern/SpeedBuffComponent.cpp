// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBuffComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

USpeedBuffComponent::USpeedBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USpeedBuffComponent::OnActivateEfect()
{
	ChengeSpeed(_SpeedDelta);
}

void USpeedBuffComponent::OnDeactivateEfect()
{
	ChengeSpeed(1.f/ _SpeedDelta);
}

void USpeedBuffComponent::ChengeSpeed(float deltaSpeed)
{
	auto* character = Cast<ACharacter>(GetOwner());
	if (character)
	{
		Cast<UCharacterMovementComponent>(character->GetMovementComponent())->MaxWalkSpeed *= deltaSpeed;
	}
}