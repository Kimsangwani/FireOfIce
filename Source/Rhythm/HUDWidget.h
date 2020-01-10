// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rhythm.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void AccuracyText();

private:
	UPROPERTY()
		class UTextBlock* Accuracy;

	FVector2D InitScreenLocation;
	FVector2D FinalScreenLocation;

	FTimerHandle DestroyTimerHandle;

	TWeakObjectPtr<class ARhythmGameState> CurrentGameState;
	
private:
	void DestroyWidget();

public:
	void SetInitWidget(FVector2D _InitScreenLocation);
	void BindGameState(class ARhythmGameState* GameState);

};
