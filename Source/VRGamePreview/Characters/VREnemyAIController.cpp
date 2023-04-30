// Fill out your copyright notice in the Description page of Project Settings.


#include "VREnemyAIController.h"

#include "NavigationSystem.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"


AVREnemyAIController::AVREnemyAIController()
{
}


void AVREnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckDistanceToRanPoint();
	
	if (CheckDistanceToRanPoint())
	{
		LifeImitation();
	}
}

void AVREnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AVREnemyAIController::LifeImitation, 1.0f, false);
}

bool AVREnemyAIController::CheckDistanceToRanPoint()
{
	float Distance = FVector::Distance(GetPawn()->GetActorLocation(), ResultLocation.Location);

	return Distance < 100.0f;
}

FVector AVREnemyAIController::CreateRandomPoint()
{
	AActor* ControllerPawn = GetPawn();
	
	UWorld* World = GetWorld();

	if (World)
	{
		// Get the navigation system.
		UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(World);

		if (NavigationSystem)
		{
			// Call the function.
			//FNavLocation ResultLocation;
			bool bFoundLocation = NavigationSystem->GetRandomReachablePointInRadius
				(ControllerPawn->GetActorLocation(), 1000.0f, ResultLocation);
		}
	}
	return ResultLocation;
}

void AVREnemyAIController::LifeImitation()
{
	CreateRandomPoint();
	MoveToLocation(ResultLocation);
}

