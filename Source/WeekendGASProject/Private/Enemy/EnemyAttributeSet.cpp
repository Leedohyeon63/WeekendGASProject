// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyAttributeSet.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	InitHealth(100.0f);
	InitMaxHealth(100.0f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	//값 검증 및 제한 용도, 순수한 수학적 처리 용도
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())//이 함수가 health attribute가 변경되어서 호출된 함수이면
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute == GetMaxHealthAttribute())	// MaxHealth가 변경되었는데
	{
		if (NewValue < GetHealth())	// Health가 MaxHealth의 새 값보다 크다면
		{
			UAbilitySystemComponent* AlilityComp = GetOwningAbilitySystemComponentChecked();
			AlilityComp->ApplyModToAttribute(GetHealthAttribute(), EGameplayModOp::Override, NewValue);
		}
	}
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
