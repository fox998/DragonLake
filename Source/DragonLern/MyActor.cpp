// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Kismet/KismetSystemLibrary.h"

#include <string>
// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformanceTest();
}

void AMyActor::PerformanceTest()
{
	auto const startTime = FDateTime::Now();
	for (int i = 0; i < mLoopIterationCount; ++i)
	{
		FHitResult hitResult;
		UKismetSystemLibrary::LineTraceSingle(GetWorld(), FVector{ 0,0,0 }, FVector{ mLineEnd , mLineEnd , mLineEnd }, ETraceTypeQuery::TraceTypeQuery1, false, {}, EDrawDebugTrace::None, hitResult, false);
	}

	auto const duration = FDateTime::Now() - startTime;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::SanitizeFloat(duration.GetTotalSeconds(), 6));
}

