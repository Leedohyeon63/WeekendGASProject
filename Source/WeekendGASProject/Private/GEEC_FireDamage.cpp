// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEC_FireDamage.h"
#include "Enemy/EnemyAttributeSet.h"

struct FFireDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	FFireDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, Health, Target, false);
	}
};

static FFireDamageStatics& FireDamageStatics()
{
	static FFireDamageStatics Statics;
	return Statics;
}

UGEEC_FireDamage::UGEEC_FireDamage()
{
	RelevantAttributesToCapture.Add(FireDamageStatics().HealthDef);	// 캡쳐할 어트리뷰트 목록에 추가

	Tag_DebuffBurn = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burn"));	// 태그 미리 저장해 놓기
	Tag_ElementFire = FGameplayTag::RequestGameplayTag(FName("Element.Fire"));
	//Tag_EffectDamage = FGameplayTag::RequestGameplayTag(FName("Effect.Damage"));
}

void UGEEC_FireDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// 이팩트를 주고 받는 ASC를 찾아 놓기
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

	if (TargetASC && SourceASC)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

		const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();	// 소스의 태그 가져오기
		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();	// 타겟의 태그 가져오기

		float Damage = MinimumDamage;

		if (SourceTags && SourceTags->HasTag(Tag_ElementFire)
			&& TargetTags && TargetTags->HasTag(Tag_DebuffBurn))
		{
			Damage *= DamageMultiplier;
		}

		if (Damage > 0.0f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					FireDamageStatics().HealthProperty,	// Health 어트리뷰트를 변경한다.
					EGameplayModOp::Additive,			// 더해 줄거다.
					-Damage								// -Damage만큼 처리
				)
			);
		}
	}
}