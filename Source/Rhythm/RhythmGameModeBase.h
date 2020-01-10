// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rhythm.h"
#include "GameFramework/GameModeBase.h"
#include "RhythmGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHM_API ARhythmGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARhythmGameModeBase();

protected:
	virtual void PostInitializeComponents() override;

public:
	void SetGameCleard();
	void SetAccuracyText(FString AccuracyText);

private:
	UPROPERTY()
		class ARhythmGameState* RhythmGameState;
};
