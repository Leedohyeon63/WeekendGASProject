// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "MainPlayer.generated.h"

class UWidgetComponent;
class UPlayerAttributeSet;

UCLASS()
class WEEKENDGASPROJECT_API AMainPlayer : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	};
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

private:
	UPROPERTY()
	TObjectPtr<UPlayerAttributeSet> PlayerAttributeSet = nullptr;

	FGameplayTag TagEffectDamage;

	FActiveGameplayEffectHandle TestInfinite;

	void OnManaChange(const FOnAttributeChangeData& InData);
	void OnMaxManaChange(const FOnAttributeChangeData& InData);
};
