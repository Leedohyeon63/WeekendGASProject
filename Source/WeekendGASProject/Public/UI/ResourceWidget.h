// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Resource.h"
#include "ResourceWidget.generated.h"
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class WEEKENDGASPROJECT_API UResourceWidget : public UUserWidget, public IResource
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void UpdateCurrent_Implementation(float InValue) override;

	UFUNCTION(BlueprintCallable)
	virtual void UpdateMax_Implementation(float InValue)override;

	UFUNCTION(BlueprintCallable)
	void SetWidgetColor(FLinearColor InColor);
protected:
	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UProgressBar> BAR = nullptr;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock> Current = nullptr;

	UPROPERTY(meta = (BindWidget))
	TWeakObjectPtr<UTextBlock> Max = nullptr;
private:
	float MaxValue = 1.0f;

	float CurrentValue = 0.0f;
};
