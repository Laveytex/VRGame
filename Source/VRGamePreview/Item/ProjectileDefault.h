// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainTypes.h"

#include "ProjectileDefault.generated.h"

UCLASS()
class VRGAMEPREVIEW_API AProjectileDefault : public AActor
{
	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UStaticMeshComponent* BulletMesh = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class USphereComponent* BulletCollisionSphere = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UProjectileMovementComponent* BulletProjectileMovement = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UNiagaraComponent* BulletFXNi = nullptr;

protected:
	FProjectileInfo ProjectileSetting;
	
	int32 ProjectileDamage = 10;
	
public:	
	UFUNCTION()
	virtual void ImpactProjectile();
	
	void InitProjectile(FProjectileInfo InitParam);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AProjectileDefault();
	
	UFUNCTION()
		void BulletCollisionSphereHit(class UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
};
