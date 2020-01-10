// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"
#include "RhythmGameState.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CHECK(CurrentGameState.IsValid());

	Accuracy = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtAccuracy")));
	CHECK(nullptr != Accuracy);

	SetPositionInViewport(InitScreenLocation);
	
	Accuracy->SetText(FText::FromString(CurrentGameState->GetAccuracy()));

	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &UHUDWidget::DestroyWidget, 1.0f);
}

void UHUDWidget::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	InitScreenLocation = FMath::Vector2DInterpTo(InitScreenLocation, FinalScreenLocation, InDeltaTime, 1.0f);
	SetPositionInViewport(InitScreenLocation);
}

void UHUDWidget::AccuracyText()
{
	
}

void UHUDWidget::DestroyWidget()
{
	RemoveFromParent();
}

void UHUDWidget::SetInitWidget(FVector2D _InitScreenLocation)
{
	InitScreenLocation = _InitScreenLocation;
	int X = FMath::RandRange(0, 1);
	float LocationX;
	if (X == 0)
	{
		LocationX = FMath::FRandRange(InitScreenLocation.X, InitScreenLocation.X + 100.0f);
	}
	else if(X == 1)
	{
		LocationX = FMath::FRandRange(InitScreenLocation.X - 100.0f, InitScreenLocation.X);
	}

	int Y = FMath::RandRange(0, 1);
	float LocationY;
	if (Y == 0)
	{
		LocationY = FMath::FRandRange(InitScreenLocation.Y, InitScreenLocation.Y + 100.0f);
	}
	else if (Y == 1)
	{
		LocationY = FMath::FRandRange(InitScreenLocation.Y - 100.0f, InitScreenLocation.Y);
	}

	FinalScreenLocation = FVector2D(LocationX, LocationY);
}

void UHUDWidget::BindGameState(ARhythmGameState * GameState)
{
	CHECK(nullptr != GameState);

	CurrentGameState = GameState;
}
