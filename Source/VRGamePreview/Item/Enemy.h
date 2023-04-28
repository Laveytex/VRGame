// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageTakerInterface.h"
#include "Enemy.generated.h"

UCLASS()
class VRGAMEPREVIEW_API AEnemy : public ACharacter, public IDamageTakerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class USceneComponent* SceneComponent = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components)
	class UCapsuleComponent* CollideComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
	float MaxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Health)
	float CurrenHealth = 100.0f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	AEnemy();
	
	virtual void Tick(float DeltaTime) override;
	
	// Flags
	bool isDie = false;

	void Die();

public:
	
	void ApplyDamage(float IncomingDamage);

	UFUNCTION(BlueprintImplementableEvent)
	void OnTakeDamage(float Damage);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
