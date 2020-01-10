// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rhythm.h"
#include "Blueprint/UserWidget.h"
#include "GameResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHM_API UGameResultWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnReturnToTitleClicked();

	UFUNCTION()
		void OnRetryGameClicked();
	
protected:
	UPROPERTY()
		class UButton* ReturnToTitleButton;

	UPROPERTY()
		class UButton* RetryGameButton;

private:
	UPROPERTY()
		class UTextBlock* Result;

public:
	void BindGameState(class ARhythmGameState* GameState);

private:
	TWeakObjectPtr<class ARhythmGameState> CurrentGameState;
};
