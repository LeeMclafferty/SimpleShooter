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

