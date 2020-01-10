// Fill out your copyright notice in the Description page of Project Settings.

#include "RhythmGameModeBase.h"
#include "Mover.h"
#include "RhythmPlayerController.h"
#include "RhythmGameState.h"
#include "RhythmPlayerState.h"

ARhythmGameModeBase::ARhythmGameModeBase()
{
	DefaultPawnClass = AMover::StaticClass();
	PlayerControllerClass = ARhythmPlayerController::StaticClass();
	GameStateClass = ARhythmGameState::StaticClass();
	PlayerStateClass = ARhythmPlayerState::StaticClass();
}

void ARhythmGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	RhythmGameState = Cast<ARhythmGameState>(GameState);
}

void ARhythmGameModeBase::SetGameCleard()
{
	RhythmGameState->SetGameCleard();

	auto RhythmPlayerController = Cast<ARhythmPlayerController>(GetWorld()->GetFirstPlayerController());
	RhythmPlayerController->ShowResultUI();
}

void ARhythmGameModeBase::SetAccuracyText(FString AccuracyText)
{
	RhythmGameState->SetAccuracy(AccuracyText);
}
