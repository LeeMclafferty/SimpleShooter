// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooter/AI/ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
	{
		SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Doing this in Tick is probably not the best way.
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	/* You do not have to pass in a nav mesh because in the BP created from this class there is a component called 
	Path Following Component that does it for you.*/
	if (PlayerPawn)
	{
		MoveToActor(PlayerPawn, 200.f);

		if (LineOfSightTo(PlayerPawn))
		{
			SetFocus(PlayerPawn);
			MoveToActor(PlayerPawn, AcceptanceRadius);
		}
		else
		{
			ClearFocus(EAIFocusPriority::Gameplay);
			StopMovement();
		}
	}
}


