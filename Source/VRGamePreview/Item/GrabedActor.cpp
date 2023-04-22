// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabedActor.h"

// Sets default values
AGrabedActor::AGrabedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGrabedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrabedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

