// Fill out your copyright notice in the Description page of Project Settings.


#include "PushActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APushActor::APushActor()
{
	// StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'
	// StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_meshComponent->SetStaticMesh(MeshRef.Object);
	
	
	_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	_sphere->OnComponentBeginOverlap.AddDynamic(this, &APushActor::OnActorBeginOverlap);
	_sphere->SetSphereRadius(100);

	RootComponent = _sphere;

	_meshComponent->AttachTo(_sphere);
}

// Called when the game starts or when spawned
void APushActor::BeginPlay()
{
	Super::BeginPlay();
	//this->ActorGetDistanceToCollision()
}

// Called every frame
void APushActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APushActor::OnActorBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	auto* character = Cast<ACharacter>(OtherActor);
	if (character)
	{
		auto* movement = Cast<UCharacterMovementComponent>(character->GetMovementComponent());
		movement->AddImpulse((character->GetActorLocation() - GetActorLocation()) * _forceStrength);
	}
}



