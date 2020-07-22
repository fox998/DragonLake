// Fill out your copyright notice in the Description page of Project Settings.


#include "Lamp.h"

// Sets default values
ALamp::ALamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	
	_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	_sphere->OnComponentBeginOverlap.AddDynamic(this, &ALamp::OnActorBeginOverlap);
	_sphere->OnComponentEndOverlap.AddDynamic(this, &ALamp::OnActorEndOverlap);
	
	RootComponent = _sphere;

	_light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	_light->SetLightColor(FColor::Red);
	_light->SetVisibility(false);
	_light->AttachTo(_sphere);
}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ALamp::OnActorBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("BeginOverlap")));
	_light->SetVisibility(true);
}


void ALamp::OnActorEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("EndOverlap")));
	_light->SetVisibility(false);
}
