// Fill out your copyright notice in the Description page of Project Settings.

#include "RhythmGameState.h"

ARhythmGameState::ARhythmGameState()
{
	bGameCleard = false;
}

bool ARhythmGameState::IsGameCleard() const
{
	return bGameCleard;
}

void ARhythmGameState::SetGameCleard()
{
	bGameCleard = true;
}

void ARhythmGameState::SetAccuracy(FString _Accuracy)
{
	Accuracy = _Accuracy;
}

FString ARhythmGameState::GetAccuracy() const
{
	return Accuracy;
}

