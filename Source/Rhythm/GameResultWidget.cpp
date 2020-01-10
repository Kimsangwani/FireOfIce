// Fill out your copyright notice in the Description page of Project Settings.


#include "GameResultWidget.h"
#include "RhythmPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RhythmGameState.h"

void UGameResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (nullptr != ReturnToTitleButton)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &UGameResultWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (nullptr != RetryGameButton)
	{
		RetryGameButton->OnClicked.AddDynamic(this, &UGameResultWidget::OnRetryGameClicked);
	}

	Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtResult")));
	CHECK(nullptr != Result);
	Result->SetText(FText::FromString(CurrentGameState->IsGameCleard() ? TEXT("Complete") : TEXT("Faild")));
}

void UGameResultWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UGameResultWidget::OnRetryGameClicked()
{
	auto RhythmPlayerController = Cast<ARhythmPlayerController>(GetOwningPlayer());
	CHECK(nullptr != RhythmPlayerController);
	RhythmPlayerController->RestartLevel();
}

void UGameResultWidget::BindGameState(ARhythmGameState * GameState)
{
	CHECK(nullptr != GameState);
	CurrentGameState = GameState;
}
