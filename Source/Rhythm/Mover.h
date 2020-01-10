// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rhythm.h"
#include "GameFramework/Pawn.h"
#include "Components/TimelineComponent.h"
#include "Mover.generated.h"

UCLASS()
class RHYTHM_API AMover : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMover();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = Mover, meta = (AllowPrivateAccess = true))
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, Category = Mover, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* Fire;
	UPROPERTY(VisibleAnywhere, Category = Mover, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* Ice;
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = true))
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = true))
		UCameraComponent* Camera;
private:
	float AngleAxis;
	float MoverLocationZ;
	float RotateDistance;
	
	FVector CurrentLocation;

	UPROPERTY()
		class ALevelGenerator* LevelGenarator;

	bool bIsFirePlaying;
	float Perfect;
	float Good;

	UPROPERTY()
		class UTimelineComponent* MoveTimeline;

	UPROPERTY()
		UCurveFloat* FloatCurve;

	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent TimelineFinished{};

	FVector InteractTileLocation;
	FVector PreviousTileLocation;

	FVector InitialLocation;
	float CurrentRoatation;
	FVector Radius;
	float StartingAngle;
	float RotationSpeed;
	bool bClockwise;
	

private:
	void Rotate(float DelataTime);
	FVector GetMeshZSize();
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION()
		void TimelineCallback(float Value);

	UFUNCTION()
		void TimelineFinishedCallback();

	void PlayTimeline();
public:
	void InitLocation(FVector Location);
	void SetLevelGenarator(class ALevelGenerator* _LevelGenarator);
	FVector GetCurrentLocation() const;
	void Swap(FVector PlaceLocation);
};
