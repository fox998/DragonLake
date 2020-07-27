// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "PickableItemBuilder.h"


// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = _itemSpawnDelta;
	_box = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn area"));
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	_items.AddZeroed(_itemMaxNumber);

	for (auto& item : _items)
	{
		item = GWorld->SpawnActor<APickableItem>(GetActorLocation(), {});
	}

}

struct MyStruct : public PickableEfectBase
{
	void ApplyEfect(OverlapParams const&) override
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString::Printf(TEXT("MyStruct::ApplyEfect")));
	};
};

FVector ASpawner::getItemLocation()
{
	const FRotator rot(0, FMath::RandRange(0, 360), 0);
	FVector shift = rot.RotateVector(FVector(_itemMinDistance, 0, 0));
	FVector playerLoration = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	return shift + playerLoration;
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	APickableItem** hiddenItemIter = _items.FindByPredicate([](APickableItem* item) {
		return item && item->IsHidden();
	});

	if (hiddenItemIter && *hiddenItemIter)
	{
		APickableItem* hiddenItem = *hiddenItemIter;
		UPickableItemBuilder::AsamblePickableItem(hiddenItem, UPickableItemBuilder::GetRandomEfect());


		hiddenItem->SetLifetime(_itemLifeTime);
		hiddenItem->SetActorHiddenInGame(false);
		hiddenItem->SetActorLocation(getItemLocation());
		
		//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString::Printf(TEXT("ASpawner::Tick")));
	}
}

