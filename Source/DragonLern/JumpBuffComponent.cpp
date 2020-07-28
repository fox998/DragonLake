// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpBuffComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

void UJumpBuffComponent::OnActivateEfect()
{
	ChengeJumpHeight(_JumpDelta);
}

void UJumpBuffComponent::OnDeactivateEfect()
{
	ChengeJumpHeight(1.f / _JumpDelta);
}

void UJumpBuffComponent::ChengeJumpHeight(float deltaSpeed)
{
	auto* character = Cast<ACharacter>(GetOwner());
	if (character)
	{
		//MaxWalkSpeed
		Cast<UCharacterMovementComponent>(character->GetMovementComponent())->JumpZVelocity *= deltaSpeed;
	}
}