// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRGamePreview/Game/DamageTakerInterface.h"
#include "Enemy.generated.h"

UCLASS()
class VRGAMEPREVIEW_API AEnemy : public ACharacter, public IDamageTakerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class USceneComponent* SceneComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	class UHealthComponent* HealthComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
	float MaxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
	float CurrenHealth = 100.0f;
	
protected:
	
	AEnemy();


public:
	
	void TakeDamage(int IncomingDamage);

	UFUNCTION()
	void Die();

	UFUNCTION(BlueprintImplementableEvent)
	void TakeDamageBP(int Damage);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	
	bool IsDead = false;
};
