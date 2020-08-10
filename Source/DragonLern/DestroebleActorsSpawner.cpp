// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroebleActorsSpawner.h"
#include "Components/SphereComponent.h"
#include "DestroyableActor.h"
#include "DestroyActorComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestroebleActorsSpawner::ADestroebleActorsSpawner()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> const CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> const ConeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> const CylinderMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> const SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	_SpawnetOpbjectsParams.Add({ CubeMesh.Object, 5 });
	_SpawnetOpbjectsParams.Add({ ConeMesh.Object, 10 });
	_SpawnetOpbjectsParams.Add({ CylinderMesh.Object, 15 });
	_SpawnetOpbjectsParams.Add({ SphereMesh.Object, 20 });

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 10;

	_Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	_Sphere->SetHiddenInGame(false);

	RootComponent = _Sphere;
}

// Called when the game starts or when spawned
void ADestroebleActorsSpawner::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ADestroebleActorsSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto* actor = GWorld->SpawnActor<ADestroyableActor>(GetActorLocation(), {});

	{
		uint32 const paramsIndex = FMath::Rand() % _SpawnetOpbjectsParams.Num();
		FSpawneedObjectParams const& objectParams = _SpawnetOpbjectsParams[paramsIndex];
		actor->_MeshComponent->SetStaticMesh(objectParams._Mesh);

		auto* destroyComponent = NewObject<UDestroyActorComponent>(actor, UDestroyActorComponent::StaticClass());
		float const timeSinceGameStart = UGameplayStatics::GetUnpausedTimeSeconds(GetWorld());
		float const destroyComponentActivationTimeDelta = FMath::Max<float>(0,  _DestroyComponentActivationTimeFromGameStart - timeSinceGameStart);
		destroyComponent->SetDestroyTime(objectParams._LifeTime + destroyComponentActivationTimeDelta);
		destroyComponent->RegisterComponent();

		actor->AddOwnedComponent(destroyComponent);
	}

	{
		const FRotator rot(0, FMath::RandRange(0, 360), 0);
		FVector shift = rot.RotateVector(FVector(_ItemMinDistance, 0, 0));
		actor->SetActorLocation(GetActorLocation() + shift);
	}

}

AActor* ADestroebleActorsSpawner::GetNewActor() const
{
	return nullptr;
}

