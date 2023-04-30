// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabedActor.h"
#include "MotionControllerComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AGrabedActor::AGrabedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact component"));
	InteractBox->SetSimulatePhysics(true);
	InteractBox->SetCollisionProfileName(TEXT("Interact"));
	InteractBox->SetupAttachment(SceneComponent);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor static mesh"));
	StaticMesh->SetCollisionProfileName(TEXT("PhysicalBody"));
	StaticMesh->SetupAttachment(InteractBox);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Actor skelital mesh"));
	SkeletalMesh->SetCollisionProfileName(TEXT("PhysicalBody"));
	SkeletalMesh->SetupAttachment(InteractBox);
	
}

// Called when the game starts or when spawned
void AGrabedActor::BeginPlay()
{
	Super::BeginPlay();

	bSimulatePhysics = StaticMesh->IsSimulatingPhysics();

	MeshInit();
}

// Called every frame
void AGrabedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*void AGrabedActor::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
}*/

void AGrabedActor::MeshInit()
{
	if (SkeletalMesh && !IsValid(SkeletalMesh))
	{
		SkeletalMesh->DestroyComponent(true);
	}

	if (StaticMesh && !StaticMesh->GetStaticMesh())
	{
		StaticMesh->DestroyComponent(true);
	}
}

void AGrabedActor::Grab_Implementation(UMotionControllerComponent* MotionController)
{
	if (!bUsing)
	{
		bUsing = true;
		CurrentMotionController = MotionController;

		FTransform ControllerTransform = CurrentMotionController->GetComponentTransform();
		InteractBox->SetSimulatePhysics(false);

		if (AttachState == EAttachState::Snap)
		{
			InteractBox->SetWorldLocation(ControllerTransform.GetLocation()
			- InteractBox->GetScaledBoxExtent().Z);
			
		
			InteractBox->SetWorldRotation(FRotator(
				0, ControllerTransform.Rotator().Yaw, ControllerTransform.Rotator().Roll));
		}
		/*else if (AttachState == EAttachState::Free)
		{
			
		}*/
		
		InteractBox->AttachToComponent(CurrentMotionController,
			FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	}
}

void AGrabedActor::Drop_Implementation(UMotionControllerComponent* MotionController)
{
	if ((MotionController == nullptr) || (CurrentMotionController == MotionController))
	{
		bUsing = false;

		InteractBox->SetSimulatePhysics(bSimulatePhysics);
		CurrentMotionController = nullptr;
		
		InteractBox->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}

void AGrabedActor::TriggerPressed_Implementation(UMotionControllerComponent* MotionController)
{
	
}


void AGrabedActor::TriggerReleased_Implementation(UMotionControllerComponent* MotionController)
{
	
}
