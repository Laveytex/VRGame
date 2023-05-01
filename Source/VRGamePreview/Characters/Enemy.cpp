// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &AEnemy::Die);
	HealthComponent->OnDamage.AddUObject(this, &AEnemy::TakeDamage);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}


void AEnemy::TakeDamage(int IncomingDamage)
{
	if (!IsDead)
	{
		HealthComponent->TakeDamage(IncomingDamage);
		TakeDamageBP(IncomingDamage);
	}
}

void AEnemy::Die()
{
	IsDead = true;
	
	GetCapsuleComponent()->DestroyComponent();
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdall"));
	GetMovementComponent()->StopActiveMovement();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

