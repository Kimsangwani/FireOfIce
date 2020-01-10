// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rhythm.h"
#include "GameFramework/GameStateBase.h"
#include "RhythmGameState.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHM_API ARhythmGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ARhythmGameState();

public:
	bool IsGameCleard() const;
	void SetGameCleard();
	void SetAccuracy(FString _Accuracy);
	FString GetAccuracy() const;
private:
	UPROPERTY(Transient)
		bool bGameCleard;

	UPROPERTY(Transient)
		FString Accuracy;
};
