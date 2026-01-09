// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyBAR.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyBAR : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WEEKENDGASPROJECT_API IEnemyBAR
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateCurrentHealth(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateMaxHealth(float InValue);
};
