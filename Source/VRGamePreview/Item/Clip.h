// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRGamePreview/Game/GrabInterface.h"

#include "Clip.generated.h"


UCLASS()
class VRGAMEPREVIEW_API AClip : public AActor, public IGrabInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UStaticMeshComponent* ClipMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UBoxComponent* ClipCollisionBox = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AClip();

public:	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void Grab(class UMotionControllerComponent* MotionController);

	virtual void Grab_Implementation(class UMotionControllerComponent* MotionController) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void Drop(class UMotionControllerComponent* MotionController);

	virtual void Drop_Implementation(class UMotionControllerComponent* MotionController) override;

protected:
	bool bUsing = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grab")
	class UMotionControllerComponent* CurrentMotionController;

	bool bSimulatePhysics = false;

};
