// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollideComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollideComponent"));
	CollideComponent->SetupAttachment(GetCapsuleComponent());
}


void AEnemy::ApplyDamage(float IncomingDamage)
{
	if (!isDie)
	{
		OnTakeDamage(IncomingDamage);
		CurrenHealth = CurrenHealth - IncomingDamage;
	}
	if (CurrenHealth <= 0)
	{
		isDie = true;
		Die();
	}
}

void AEnemy::Die()
{
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName(TEXT("Ragdall"));
		CollideComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMovementComponent()->StopActiveMovement();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

