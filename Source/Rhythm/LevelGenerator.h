// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rhythm.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

UCLASS()
class RHYTHM_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = Root)
		USceneComponent* Root;

private:
	void InitSpawnTile();
	void InitMover();
	void SpawnTile();
	void RemovePreviousTiles();
private:
	UPROPERTY(EditAnywhere, Category = Setup, meta = (AllowPrivateAccess = true))
		TSubclassOf<class ATile> TileClass;

	int32 AmountToSpawn;
	int32 BeginAmount;
	int32 Index;

	FVector2D TileSize;

	FVector LastPosition;

	TArray<class ATile*> Tiles;
	TArray<class ATile*> RemoveTiles;


public:
	FVector GetInteractTileLocation() const;
	FVector GetPreviousTileLocation() const;
	void IncreaseIndex();
	
};
