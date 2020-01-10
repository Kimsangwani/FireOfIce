// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Mover.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	
	RootComponent = Tile;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Tile(TEXT("/Game/Resource/Actor/SM_Tile.SM_Tile"));
	if (SM_Tile.Succeeded())
	{
		Tile->SetStaticMesh(SM_Tile.Object);
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::DestroyTile()
{
	Destroy();
}

FVector ATile::GetMeshZSize()
{
	FVector BoxExtent = Tile->CalcBounds(Tile->GetComponentTransform()).BoxExtent;

	return BoxExtent;
}

