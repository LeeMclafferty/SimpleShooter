// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooter/AI/MyBTTask_Shoot.h"
#include "Kismet/GameplayStatics.h"

#include "SimpleShooter/AI/ShooterAIController.h"
#include "SimpleShooter/Player/ShooterCharacter.h"

UMyBTTask_Shoot::UMyBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UMyBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (AShooterAIController* AiController = Cast<AShooterAIController>(OwnerComp.GetAIOwner()))
	{
		if (AShooterCharacter* AiPawn = Cast<AShooterCharacter>(AiController->GetPawn()))
		{
			AiPawn->Shoot();
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
