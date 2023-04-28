// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainTypes.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VRGAMEPREVIEW_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSetting")
	UDataTable* WeaponInfoTable = nullptr;
	
	UFUNCTION(BlueprintCallable)
	bool GetWeaponInfoByName(FName NameWeapon, FWeaponInfo& OutInfo);
};
