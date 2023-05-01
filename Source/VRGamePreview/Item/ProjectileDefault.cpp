// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileDefault.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "VRGamePreview/Game/DamageTakerInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileDefault::AProjectileDefault()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	BulletCollisionSphere->SetCollisionProfileName(TEXT("BlockAll"));
	BulletCollisionSphere->bReturnMaterialOnMove = true; //hit event return physMat
	BulletCollisionSphere->SetCanEverAffectNavigation(false); //collision not affect on navigation
	BulletCollisionSphere->SetSphereRadius(16.f);

	BulletCollisionSphere->OnComponentHit.AddDynamic(this, &AProjectileDefault::BulletCollisionSphereHit);
	
	RootComponent = BulletCollisionSphere;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet projectile mash"));
	BulletMesh->SetCanEverAffectNavigation(false);
	BulletMesh->SetupAttachment(RootComponent);

	BulletProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Projectilemovement"));
	BulletProjectileMovement->InitialSpeed = 1.f;
	BulletProjectileMovement->MaxSpeed = 0.f;
	BulletProjectileMovement->UpdatedComponent = RootComponent;

	BulletProjectileMovement->bRotationFollowsVelocity = true;
	BulletProjectileMovement->bShouldBounce = true;

	BulletFXNi = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BulletNi FX"));
	BulletFXNi->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectileDefault::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileDefault::InitProjectile(FProjectileInfo InitParam)
{
	BulletProjectileMovement->InitialSpeed = InitParam.ProjectileInitSpeed;
	BulletProjectileMovement->MaxSpeed = InitParam.ProjectileInitSpeed;
	BulletProjectileMovement->ProjectileGravityScale = InitParam.isGravityInfluence;
	this->SetLifeSpan(InitParam.ProjectileLifeTime);
	
	ProjectileDamage = FMath::RandRange(InitParam.ProjectileMinDamage, InitParam.ProjectileMaxDamage);;

	if (InitParam.TrailFXNi)
		BulletFXNi->SetAsset(InitParam.TrailFXNi);	
}

void AProjectileDefault::BulletCollisionSphereHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	IDamageTakerInterface * damageTakerActor = Cast<IDamageTakerInterface>(OtherActor);
	
	if (damageTakerActor)
	{
		damageTakerActor->TakeDamage(ProjectileDamage);
	}
	
	ImpactProjectile();
}

void AProjectileDefault::ImpactProjectile()
{
	Destroy();
}
