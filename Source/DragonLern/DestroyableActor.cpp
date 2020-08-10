// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyableActor.h"

// Sets default values
ADestroyableActor::ADestroyableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _MeshComponent;
}

// Called when the game starts or when spawned
void ADestroyableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

