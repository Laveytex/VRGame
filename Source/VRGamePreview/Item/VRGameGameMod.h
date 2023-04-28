// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "VRGameGameMod.generated.h"

/**
 * 
 */
UCLASS()
class VRGAMEPREVIEW_API AVRGameGameMod : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	AVRGameGameMod();

	virtual void BeginPlay() override;
};
