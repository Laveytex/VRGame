// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "MainTypes.generated.h"


UCLASS()
class VRGAMEPREVIEW_API UMainTypes : public  UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class EAttachState : uint8
{
	Snap UMETA(DisplayName = "Snap Component State"),
	Free UMETA(DisplayName = "Free Component State")
};

USTRUCT(BlueprintType)
struct FDropMeshInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropMesh")
	UStaticMesh* DropMesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropMesh ")
	FTransform DropMeshOffset = FTransform();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropMesh ")
	FVector DropMeshImpulseDirection = FVector(0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropMesh ")
	float PowerImpulse = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropMesh ")
	float ImpulseRandomDispersion = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropMesh ")
	float CustomMass = 0.0f;
};


USTRUCT(BlueprintType)
struct FProjectileInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
	TSubclassOf<class AProjectileDefault> Projectile = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
	UNiagaraSystem* TrailFXNi = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
	int ProjectileMinDamage = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
	int ProjectileMaxDamage = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
	float ProjectileLifeTime = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
	float ProjectileInitSpeed = 2000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ProjectileSetting")
	bool isGravityInfluence = false;
};

USTRUCT(BlueprintType)
struct FWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float RateOfFire = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	int32 MaxRound = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool isSingleShoot = false;
	
	// Create for trace
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float WeaponDamage = 20.0f;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* SoundFireWeapon = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	UNiagaraSystem* EffectFireWeaponNi = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropMesh")
	FDropMeshInfo ShellDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DropMesh")
	FDropMeshInfo ClipDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FProjectileInfo ProjectileSetting;
};

USTRUCT(BlueprintType)
struct FAddicionalWeaponInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon States")
	int32 Round = 10;
};

