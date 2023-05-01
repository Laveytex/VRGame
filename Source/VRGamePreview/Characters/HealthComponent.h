// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRGAMEPREVIEW_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_EVENT(UHealthComponent, FOnDie)
	DECLARE_EVENT_OneParam(UHealthComponent,FOnHealthChanged, int32)
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPawnOnDie);
	

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
	int32 MaxHealth = 100;

	UFUNCTION(BlueprintCallable)
	int32 GetHeath() const;
	
	int32 GetHealthState() const;
	
	FOnDie OnDie;
	FOnHealthChanged OnDamage;

	UPROPERTY(BlueprintAssignable)
	FPawnOnDie PawnOnDie;
	
	UPROPERTY(BlueprintReadWrite, Category = "Component")
	class APawn* Owner = nullptr;

	
protected:
	
	UPROPERTY()
	int32 CurrentHealth;

public:	

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int InpactDamage);
	
	void AddHealth(int AddiditionalHeathValue);

protected:
	
	UHealthComponent();
		
};
