// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorsTracker.h"
#include "Components/InputComponent.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
AActorsTracker::AActorsTracker()
{
	// Slate
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AActorsTracker::BeginPlay()
{
	Super::BeginPlay();

	_PlayerController = GetWorld()->GetFirstPlayerController();
	_PlayerController->InputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &AActorsTracker::SelectActorUnderCursor);
	_PlayerController->InputComponent->BindKey(EKeys::R, IE_Pressed, this, &AActorsTracker::DisplayAllActorsBetweenSelected);
	_PlayerController->InputComponent->BindKey(EKeys::E, IE_Pressed, this, &AActorsTracker::LogAllActorsInViewport);
	_PlayerController->bShowMouseCursor = true;
}

// Called every frame
void AActorsTracker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorsTracker::SelectActorUnderCursor()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Blue, TEXT("LeftMouseButton presed"));
	
	FVector mousePosition;
	FVector mouseDirection;
	_PlayerController->DeprojectMousePositionToWorld(mousePosition, mouseDirection);
	FVector const traceEnd = mousePosition + mouseDirection * _TraceVectorLength;

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;

	bool const isHit = GetWorld()->LineTraceSingleByChannel(OutHit, mousePosition, traceEnd, ECC_Visibility, CollisionParams);
	if (isHit)
	{
		AActor* const selectedActor = OutHit.Actor.Get();
		_SelectedActors.push_back(selectedActor);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Selected %s"), *selectedActor->GetName()));

		if (_SelectedActors.size() > 2)
		{
			_SelectedActors.pop_front();
		}
	}
}

void AActorsTracker::DisplayAllActorsBetweenSelected()
{
	if (_SelectedActors.size() >= 2)
	{
		FVector const traceStart = _SelectedActors[0]->GetActorLocation();
		FVector const traceEnd = _SelectedActors[1]->GetActorLocation();

		TArray<FHitResult> OutHits;
		FCollisionQueryParams CollisionParams;
		GetWorld()->LineTraceMultiByObjectType(OutHits, traceStart, traceEnd, FCollisionObjectQueryParams::AllObjects);
		DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Green, true, 1);

		for (auto const& hit : OutHits)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%s"), *hit.Actor->GetName()));
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Between selected :")));

	}
}

void AActorsTracker::LogAllActorsInViewport()
{
	APlayerCameraManager const* const cameraManager =  UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	cameraManager->GetFOVAngle();
	UKismetSystemLibrary::SphereTraceMultiByProfile();
}

