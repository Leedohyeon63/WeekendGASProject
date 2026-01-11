// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPawn.h"
#include "AbilitySystemComponent.h"
#include "Enemy/EnemyAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UI/ResourceWidget.h"
#include "UI/EnemyBAR.h"

AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	//컴포넌트 생성
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));
	BarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("BarWidgetComponent"));
	BarWidgetComponent->SetupAttachment(RootComponent);
}

void AEnemyPawn::ChangeHP(float Amount)
{
	if (EnemyAttributeSet)
	{
		float NewHealth = EnemyAttributeSet->GetHealth() + Amount;
		EnemyAttributeSet->SetHealth(NewHealth);
	}
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); //어빌리티 시스템 컴포넌트 초기화

		FOnGameplayAttributeValueChange& OnHealthChange =
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetHealthAttribute());

		OnHealthChange.AddUObject(this, &AEnemyPawn::OnHealthChange);

		FOnGameplayAttributeValueChange& OnMaxHealthChange =
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetMaxHealthAttribute());

		OnMaxHealthChange.AddUObject(this, &AEnemyPawn::OnMaxHealthChange);
	}

	if (EnemyAttributeSet)
	{
		if (BarWidgetComponent && BarWidgetComponent->GetWidget())
		{
			if (BarWidgetComponent->GetWidget()->Implements<UResource>())
			{
				IEnemyBAR::Execute_UpdateMaxHealth(BarWidgetComponent->GetWidget(), EnemyAttributeSet->GetMaxHealth());
				IEnemyBAR::Execute_UpdateCurrentHealth(BarWidgetComponent->GetWidget(), EnemyAttributeSet->GetHealth());
			}

		}
	}
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyAttributeSet)
	{
		FString HealthString = FString::Printf(TEXT("%.1f/%.1f"), EnemyAttributeSet->GetHealth(), EnemyAttributeSet->GetMaxHealth());
		DrawDebugString(GetWorld(), GetActorLocation(), HealthString, nullptr, FColor::White, 0, true);
	}
}

void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyPawn::OnHealthChange(const FOnAttributeChangeData& InData)
{
	if (EnemyAttributeSet)
	{
		UE_LOG(LogTemp, Log, TEXT("Health가 변경되었다 %.1f -> %.1f"), InData.OldValue, InData.NewValue);
		IEnemyBAR::Execute_UpdateCurrentHealth(BarWidgetComponent->GetWidget(), EnemyAttributeSet->GetHealth());
	}
}

void AEnemyPawn::OnMaxHealthChange(const FOnAttributeChangeData& InData)
{
	if (EnemyAttributeSet)
	{
		UE_LOG(LogTemp, Log, TEXT("On Health Change : %.1f -> %.1f"), InData.OldValue, InData.NewValue);
		IEnemyBAR::Execute_UpdateCurrentHealth(BarWidgetComponent->GetWidget(), EnemyAttributeSet->GetHealth());
	}
}
