// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabedActor.h"
#include "MotionControllerComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AGrabedActor::AGrabedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called when the game starts or when spawned
void AGrabedActor::BeginPlay()
{
	Super::BeginPlay();

	bSimulatePhysics = StaticMesh->IsSimulatingPhysics();
}

// Called every frame
void AGrabedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrabedActor::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
}

void AGrabedActor::Grab_Implementation(UMotionControllerComponent* MotionController)
{
	if (!bUsing)
	{
		bUsing = true;
		CurrentMotionController = MotionController;
		FTransform ControllerTransform = CurrentMotionController->GetRelativeTransform();
		
		StaticMesh->SetSimulatePhysics(false);
		StaticMesh->AttachToComponent(MotionController, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	}
}

void AGrabedActor::Drop_Implementation(UMotionControllerComponent* MotionController)
{
	if ((MotionController == nullptr) || (CurrentMotionController == MotionController))
	{
		bUsing = false;

		StaticMesh->SetSimulatePhysics(bSimulatePhysics);
		CurrentMotionController = nullptr;
		
		StaticMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void AGrabedActor::TriggerPressed_Implementation(UMotionControllerComponent* MotionController)
{
	Fire();
}


