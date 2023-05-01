// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "VRGamePreview/Game/DamageTakerInterface.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentHealth = MaxHealth;
}

int32 UHealthComponent::GetHeath() const
{
	return CurrentHealth;
}

int32 UHealthComponent::GetHealthState() const
{
	return CurrentHealth/MaxHealth;
}

void UHealthComponent::TakeDamage(int32 Damage)
{
	CurrentHealth -= Damage;

	if (CurrentHealth <= 0)
	{
		if(OnDie.IsBound() || PawnOnDie.IsBound())
		{
			OnDie.Broadcast();
			PawnOnDie.Broadcast();
		}
		else
		{
			if(OnDamage.IsBound())
			{
				OnDamage.Broadcast(Damage);
			}
		}
	}
}

void UHealthComponent::AddHealth(int AddiditionalHeathValue)
{
	CurrentHealth+=AddiditionalHeathValue;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}

