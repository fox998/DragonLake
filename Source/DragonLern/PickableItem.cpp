// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APickableItem::APickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	_sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickableItem::OnBeginOverlap);
	RootComponent = _sphereComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/NewFolder/PickableItemMaterial.PickableItemMaterial'"));
	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_meshComponent->SetStaticMesh(MeshRef.Object);
	_meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	_meshComponent->AttachTo(_sphereComponent);
	_meshComponent->GetStaticMesh()->SetMaterial(0, Material.Object);

	auto* matireal = _meshComponent->GetStaticMesh()->GetMaterial(0);
	_dynamicMaterial = UMaterialInstanceDynamic::Create(matireal, nullptr);
	_meshComponent->SetMaterial(0, _dynamicMaterial);

	SetActorHiddenInGame(true);
}

void APickableItem::SetColor(FColor newColor)
{
	_dynamicMaterial->SetVectorParameterValue(TEXT("Base Color"), newColor );
}

FColor APickableItem::GetColor() const
{
	FLinearColor textureColor;
	_dynamicMaterial->GetVectorParameterValue(TEXT("Base Color"), textureColor);
	return textureColor.ToFColor(true);
}

void APickableItem::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (_itemEfect && OtherActor)
	{
		_itemEfect->ApplyEfect({
			OverlappedComponent,
			OtherActor,
			OtherComp,
			OtherBodyIndex,
			bFromSweep,
			SweepResult
		});
	}

	SetActorHiddenInGame(true);
}

// Called when the game starts or when spawned
void APickableItem::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(false);
}

// Called every frame
void APickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_lifeTime -= DeltaTime;

	if (_lifeTime <= 0)
	{
		SetActorHiddenInGame(true);
	}
}

