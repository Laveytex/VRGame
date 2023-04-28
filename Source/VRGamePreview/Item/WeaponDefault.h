// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainTypes.h"
#include "GrabInterface.h"

#include "WeaponDefault.generated.h"

UCLASS()
class VRGAMEPREVIEW_API AWeaponDefault : public AActor, public IGrabInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponDefault();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class USceneComponent* SceneComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UBoxComponent* InteractionComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UStaticMeshComponent* StaticMeshWeapon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class USkeletalMeshComponent* SkeletalMeshWeapon = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UArrowComponent* ShootLocation = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UArrowComponent* ShellSpawnPoint = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UArrowComponent* ClipSpawnPoint = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UBoxComponent* ClipSlot = nullptr;

	UPROPERTY()
	FWeaponInfo WeaponSetting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Info")
	FAddicionalWeaponInfo WeaponInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grab")
	class UMotionControllerComponent* CurrentMotionController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UHapticFeedbackEffect_Base* HapticEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	FName InitWeaponName;

protected:
	//Timer`s flag
	float FireTimer = 0.0f;

	//flags
	bool BlockFire = false;
	bool ClipEmpty = false;
	bool ClipSpawn = false;
	
	FWeaponInfo myWeaponInfo;
	
	FProjectileInfo GetProjectile();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
	bool WeaponFiring  = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Grab")
	bool bUsing = false;

	bool bSimulatePhysics = false;
	
public:	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void Grab(class UMotionControllerComponent* MotionController);

	virtual void Grab_Implementation(class UMotionControllerComponent* MotionController) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void Drop(class UMotionControllerComponent* MotionController);

	virtual void Drop_Implementation(class UMotionControllerComponent* MotionController) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void TriggerPressed (class UMotionControllerComponent* MotionController);

	virtual void TriggerPressed_Implementation(class UMotionControllerComponent* MotionController) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "GrabInterface")
	void TriggerReleased(class UMotionControllerComponent* MotionController);

	virtual void TriggerReleased_Implementation(class UMotionControllerComponent* MotionController) override;
	
	UFUNCTION(BlueprintCallable)
	void SetWeaponStateFire(bool bIsFire);
	
	void Fire();

	UFUNCTION(BlueprintCallable)
	int32 GetWeaponRound();
	UFUNCTION(BlueprintCallable)
	int32 SetWeaponRound(int RoundToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void InitWeapon(FName IDWeaponName);

	void ClipDrop();
	void ShellDrop();

	void InitDropMesh(UStaticMesh* DropMesh, UArrowComponent* ArrowComponent, FTransform Offset,
	FVector DropImpulsDirection, float ImpulsRandomDispersion,
	float PowerImpuls, float CustormMass);

	UFUNCTION()
	void ClipCollisionBoxHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResul);

	//Timers
	void FireTick(float DeltaTime);
	void ClipCheck();
	


};
