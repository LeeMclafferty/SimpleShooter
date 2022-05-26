// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooter/Framework/KillThemAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"

#include "SimpleShooter/Player/ShooterCharacter.h"
#include "SimpleShooter/Player/SimpleShooterPlayerController.h"
#include "SimpleShooter/AI/ShooterAIController.h"

void AKillThemAllGameMode::PawnKilled(APawn* KilledPawn)
{
	Super::PawnKilled(KilledPawn);

	ASimpleShooterPlayerController* PlayerController = Cast<ASimpleShooterPlayerController>(KilledPawn->GetController());
	AShooterCharacter* PlayerPawn = Cast<AShooterCharacter>(KilledPawn);
	if (PlayerController)
	{
		// Game Lost
		EndGame(false);
	}

	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			return;
		}
	}

	EndGame(true);
}

void AKillThemAllGameMode::EndGame(bool IsPlayerWinner)
{
	// Ranged for loop over every actor of type AController
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// Evaluate who one and set focus on the winner.
		bool IsWinner = Controller->IsPlayerController() == IsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), IsWinner);
	}
}
