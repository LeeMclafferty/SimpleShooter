// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooter/Player/SimpleShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ASimpleShooterPlayerController::BeginPlay()
{
	HudWidget = CreateWidget(this, HudWidgetClass);
	if (HudWidget)
	{
		HudWidget->AddToViewport();
	}
}

void ASimpleShooterPlayerController::GameHasEnded(class AActor* EndGameFocus /*= nullptr*/, bool bIsWinner /*= false*/)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	HudWidget->RemoveFromParent();

	if (bIsWinner)
	{
		UUserWidget* WinWidget = CreateWidget(this, WinWidgetClass);
		if (WinWidget)
		{
			WinWidget->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseWidget = CreateWidget(this, LoseWidgetClass);
		if (LoseWidget)
		{
			LoseWidget->AddToViewport();
		}
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

}


