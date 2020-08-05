// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSnapedActor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "DragonLernCharacter.h"
#include "DrawDebugHelpers.h"
#include "UObject/NoExportTypes.h"

namespace
{
	template <typename ValueT, typename GridSizeT>
	ValueT SnapToGrid(ValueT value, GridSizeT gridSize)
	{
		return static_cast<int32_t>(value / gridSize) * gridSize;
	}
}

// Sets default values
AGridSnapedActor::AGridSnapedActor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> const MeshRef(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> const Material(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_meshComponent->SetStaticMesh(MeshRef.Object);
	_meshComponent->GetStaticMesh()->SetMaterial(0, Material.Object);
	
	_meshComponent->OnComponentHit.AddDynamic(this, &AGridSnapedActor::OnHit);

	RootComponent = _meshComponent;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridSnapedActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGridSnapedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_IsTicked = true;
}

void AGridSnapedActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->IsA<ADragonLernCharacter>() || !_IsTicked)
	{
		return;
	}
	_IsTicked = false;

	FVector const currentSelfLocation = GetActorLocation();
	FVector const otherActorLocation = OtherActor->GetActorLocation();

	FVector origin;
	FVector boxVolume;
	GetActorBounds(false, origin, boxVolume);

	if (!IsValidPlayerPosition(OtherActor, boxVolume))
	{
		return;
	}

	FVector const hitDirection = currentSelfLocation - otherActorLocation;
	uint32 const moveAxis = (FMath::Abs(hitDirection.X) > FMath::Abs(hitDirection.Y) ? 0 : 1 );
	FVector moveDirection = FVector::ZeroVector;
	moveDirection[moveAxis] = hitDirection[moveAxis];
	FVector const shiftVector = moveDirection.GetSafeNormal() * boxVolume[moveAxis] * 2;
	FVector const newLocation = currentSelfLocation + shiftVector;

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool const isHit = GetWorld()->LineTraceSingleByChannel(OutHit, currentSelfLocation, newLocation, ECC_Visibility, CollisionParams);
	if (!isHit)
	{
		SetActorLocation(newLocation);
	}
}

bool IsInBoundByAxis(FVector2D position, FVector2D bounds, uint32 axis)
{
	return FMath::Abs(position[axis]) < (bounds[axis] * 0.5);
}

bool AGridSnapedActor::IsValidPlayerPosition(AActor* otherActor, FVector actorBox) const
{
	FVector const selfLocation = GetActorLocation();
	FVector const otherActorLocation = otherActor->GetActorLocation();
	auto const distToActor = FVector2D(selfLocation - otherActorLocation);

	FVector2D const actorBounds2D(actorBox);
	
	bool const isPlayerOutOfBounds = actorBounds2D.X <= FMath::Abs(distToActor.X) || actorBounds2D.Y <= FMath::Abs(distToActor.Y);
	bool const isPlayerFacedToActor = IsInBoundByAxis(distToActor, actorBounds2D, 0) || IsInBoundByAxis(distToActor, actorBounds2D, 1);

	return isPlayerOutOfBounds && isPlayerFacedToActor;
}

