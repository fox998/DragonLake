// Fill out your copyright notice in the Description page of Project Settings.


#include "SocobanGoalActor.h"
#include "Kismet/GameplayStatics.h"
#include "SocobanGameModeComponent.h"
#include "GridSnapedActor.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
ASocobanGoalActor::ASocobanGoalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_box = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	_box->OnComponentBeginOverlap.AddDynamic(this, &ASocobanGoalActor::OnActorBeginOverlap);
	_box->OnComponentEndOverlap.AddDynamic(this, &ASocobanGoalActor::OnActorEndOverlap);
	_box->SetBoxExtent(FVector(25));
	_box->SetHiddenInGame(false);

	RootComponent = _box;

	_light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	_light->SetLightColor(FColor::Yellow);
	_light->SetVisibility(true);
	_light->AttachTo(_box);
}

// Called when the game starts or when spawned
void ASocobanGoalActor::BeginPlay()
{
	Super::BeginPlay();
	
	USocobanGameModeComponent* component = GetSocobanGameModeComponent();
	component->ResetGoals();
	component->IncreaseGoals();
}

// Called every frame
void ASocobanGoalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASocobanGoalActor::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AGridSnapedActor>())
	{
		USocobanGameModeComponent* component = GetSocobanGameModeComponent();
		component->DecreaseGoals();
		_light->SetVisibility(false);
	}
}

void ASocobanGoalActor::OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AGridSnapedActor>())
	{
		USocobanGameModeComponent* component = GetSocobanGameModeComponent();
		component->IncreaseGoals();
		_light->SetVisibility(true);
	}
}

USocobanGameModeComponent* ASocobanGoalActor::GetSocobanGameModeComponent() const
{
	AGameModeBase* gameMode = UGameplayStatics::GetGameMode(GetWorld());
	auto* component = gameMode->FindComponentByClass<USocobanGameModeComponent>();

	if (!component)
	{
		component = NewObject<USocobanGameModeComponent>(gameMode, USocobanGameModeComponent::StaticClass());
		component->RegisterComponent();
		gameMode->AddOwnedComponent(component);
	}

	return component;
}

