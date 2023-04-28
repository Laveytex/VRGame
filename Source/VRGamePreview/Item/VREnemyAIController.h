// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VREnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class VRGAMEPREVIEW_API AVREnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	AVREnemyAIController();

	FNavLocation ResultLocation;
	
	bool CheckDistanceToRanPoint();

	FVector CreateRandomPoint();

	FTimerHandle FuzeTimerHandle;

	void LifeImitation();
};
