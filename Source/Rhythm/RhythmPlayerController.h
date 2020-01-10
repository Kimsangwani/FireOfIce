// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rhythm.h"
#include "GameFramework/PlayerController.h"
#include "RhythmPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RHYTHM_API ARhythmPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARhythmPlayerController();
	void ShowResultUI();
	void ShowAccuracyText();
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UGameResultWidget> GameResultWidgetClass;

private:
	UPROPERTY()
		class UHUDWidget* HUDWidget;

	UPROPERTY()
		class UGameResultWidget* GameResultWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

private:
	void ChangeInputMode(bool bGameMode);
};
