// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelGenerator.h"
#include "Tile.h"
#include "Mover.h"
#include "RhythmPlayerController.h"
#include "RhythmGameModeBase.h"

// Sets default values
ALevelGenerator::ALevelGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	AmountToSpawn = FMath::RandRange(30, 40);
	BeginAmount = 0;
	TileSize.X = 100;
	Index = 1;
	LastPosition = FVector(0.0f, 0.0f, 0.0f);

	TileClass = ATile::StaticClass();
}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	InitSpawnTile();
	InitMover();
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelGenerator::InitSpawnTile()
{
	CHECK(nullptr != TileClass);

	for (int32 i = BeginAmount; i < AmountToSpawn; i++)
	{
		SpawnTile();
	}
}

void ALevelGenerator::InitMover()
{
	AMover* Mover = Cast<AMover>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Mover->InitLocation(FVector(Tiles[0]->GetActorLocation().X, Tiles[0]->GetActorLocation().Y, Tiles[0]->GetActorLocation().Z + Tiles[0]->GetMeshZSize().Z ));
	Mover->SetLevelGenarator(this);
}

void ALevelGenerator::SpawnTile()
{
	ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileClass, FVector::ZeroVector, FRotator::ZeroRotator);

	Tiles.Add(NewTile);

	int32 Direction = FMath::RandRange(0, 1);
	if (Direction == 0)
	{
		NewTile->SetActorLocation(FVector(LastPosition.X, LastPosition.Y - TileSize.X, LastPosition.Z));
	}
	else
	{
		NewTile->SetActorLocation(FVector(LastPosition.X + TileSize.X, LastPosition.Y, LastPosition.Z));
	}

	LastPosition = NewTile->GetActorLocation();
}

void ALevelGenerator::RemovePreviousTiles()
{
}

FVector ALevelGenerator::GetInteractTileLocation() const
{
	return Tiles[Index]->GetActorLocation();
}

FVector ALevelGenerator::GetPreviousTileLocation() const
{
	return Tiles[Index - 1]->GetActorLocation();
}

void ALevelGenerator::IncreaseIndex()
{
	if (Index == AmountToSpawn - 1)
	{
		auto RhythmGameMode = Cast<ARhythmGameModeBase>(GetWorld()->GetAuthGameMode());
		CHECK(nullptr != RhythmGameMode);
		auto RhythmPlayerController = Cast<ARhythmPlayerController>(GetWorld()->GetFirstPlayerController());
		CHECK(nullptr != RhythmPlayerController);

		RhythmGameMode->SetGameCleard();
		RhythmPlayerController->ShowResultUI();
	}
	Index++;
}



