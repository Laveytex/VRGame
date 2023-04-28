// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MotionControllerComponent.h"
#include "GrabInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGrabInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 **/
class VRGAMEPREVIEW_API IGrabInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void Grab(class UMotionControllerComponent* MotionController);	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void Drop(class UMotionControllerComponent* MotionController);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void TriggerPressed(class UMotionControllerComponent* MotionController);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void TriggerReleased(class UMotionControllerComponent* MotionController);
};
