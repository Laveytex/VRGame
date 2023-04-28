// Fill out your copyright notice in the Description page of Project Settings.


#include "Clip.h"

#include "Components/BoxComponent.h"

// Sets default values
AClip::AClip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = ClipMesh;
	
	ClipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClipMesh"));
	ClipMesh->SetCollisionProfileName(TEXT("PhysicalBody"));
	ClipMesh->SetSimulatePhysics(true);

	ClipCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ClipCollisionBox"));
	ClipCollisionBox->SetCollisionProfileName(TEXT("Interact"));
	ClipCollisionBox->SetupAttachment(ClipMesh);
}

// Called when the game starts or when spawned
void AClip::BeginPlay()
{
	Super::BeginPlay();

	bSimulatePhysics = ClipMesh->IsSimulatingPhysics();
}

void AClip::Grab_Implementation(UMotionControllerComponent* MotionController)
{
	if (!bUsing)
	{
		bUsing = true;
		CurrentMotionController = MotionController;

		FTransform ControllerTransform = CurrentMotionController->GetRelativeTransform();
		
		ClipMesh->SetSimulatePhysics(false);
		ClipMesh->AttachToComponent(MotionController, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	}
}

void AClip::Drop_Implementation(UMotionControllerComponent* MotionController)
{
	if ((MotionController == nullptr) || (CurrentMotionController == MotionController))
	{
		bUsing = false;

		ClipMesh->SetSimulatePhysics(bSimulatePhysics);
		CurrentMotionController = nullptr;
		
		ClipMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}
