// Fill out your copyright notice in the Description page of Project Settings.


#include "DecreaseSpeedBuffComponent.h"

UDecreaseSpeedBuffComponent::UDecreaseSpeedBuffComponent()
{
	_SpeedDelta = 1.f / _SpeedDelta;
}
