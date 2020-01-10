// Fill out your copyright notice in the Description page of Project Settings.

#include "RhythmPlayerController.h"
#include "HUDWidget.h"
#include "GameResultWidget.h"
#include "Mover.h"
#include "RhythmGameState.h"

ARhythmPlayerController::ARhythmPlayerController()
{
	bEnableClickEvents = true;

	static ConstructorHelpers::FClassFinder<UHUDWidget> UI_HUD_C(TEXT("/Game/Blueprint/UMG/BP_HUD.BP_HUD_C"));
	if (UI_HUD_C.Succeeded())
	{
		HUDWidgetClass = UI_HUD_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UGameResultWidget> UI_GameResult_C(TEXT("/Game/Blueprint/UMG/BP_ResultUI.BP_ResultUI_C"));
	if (UI_GameResult_C.Succeeded())
	{
		GameResultWidgetClass = UI_GameResult_C.Class;
	}
}

void ARhythmPlayerController::ShowResultUI()
{
	auto RhythmGameState = Cast<ARhythmGameState>(UGameplayStatics::GetGameState(this));
	CHECK(nullptr != RhythmGameState);

	GameResultWidget->BindGameState(RhythmGameState);
	GameResultWidget->AddToViewport();
	ChangeInputMode(false);
}

void ARhythmPlayerController::ShowAccuracyText()
{
	AMover* Mover = Cast<AMover>(GetPawn());
	CHECK(nullptr != Mover);

	FVector Location = Mover->GetActorLocation();
	FVector2D ScreenLocation;
	if (ProjectWorldLocationToScreen(Location, ScreenLocation))
	{
		auto RhythmGameState = Cast<ARhythmGameState>(UGameplayStatics::GetGameState(this));
		CHECK(nullptr != RhythmGameState);

		HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);
		CHECK(nullptr != HUDWidget);
		HUDWidget->BindGameState(RhythmGameState);
		HUDWidget->SetInitWidget(ScreenLocation);
		HUDWidget->AddToViewport();
	}
}

void ARhythmPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	GameResultWidget = CreateWidget<UGameResultWidget>(this, GameResultWidgetClass);
	CHECK(nullptr != GameResultWidgetClass);
}

void ARhythmPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}
