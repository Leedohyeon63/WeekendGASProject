// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Resource.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UResource : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WEEKENDGASPROJECT_API IResource
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateCurrent(float InValue);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Resource")
	void UpdateMax(float InValue);
};
