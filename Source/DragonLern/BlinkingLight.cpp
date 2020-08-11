// Fill out your copyright notice in the Description page of Project Settings.


#include "BlinkingLight.h"
#include "UObject/NoExportTypes.h"
#include "Components/PointLightComponent.h"

// Sets default values
ABlinkingLight::ABlinkingLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	_light->SetVisibility(true);

	RootComponent = _light;
}

// Called when the game starts or when spawned
void ABlinkingLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlinkingLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FLinearColor const lerpedColor = FMath::Lerp(FLinearColor::Yellow, FLinearColor::Blue, (FMath::Sin(GetWorld()->TimeSeconds) + 1) / 2);
	_light->SetLightColor(lerpedColor.ToFColor(true));
}

