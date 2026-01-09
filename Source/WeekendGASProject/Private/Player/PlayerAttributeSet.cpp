// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitMana(100.0f);
	InitMaxMana(100.0f);
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("현재 Mana : %.1f"), GetMana());

		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		if (GetMana() <= 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("마나 오링"));
		}
	}
}
