// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Player/PlayerAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/WidgetComponent.h"
#include "UI/PlayerResource.h"
#include "UI/ResourceWidget.h"
#include "UI/MainHUD.h"
#include "EnhancedInputComponent.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	//컴포넌트 생성
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this); //어빌리티 시스템 컴포넌트 초기화

		FOnGameplayAttributeValueChange& OnManaChange =
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute());

		OnManaChange.AddUObject(this, &AMainPlayer::OnManaChange);

		FOnGameplayAttributeValueChange& OnMaxManaChange =
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxManaAttribute());

		OnMaxManaChange.AddUObject(this, &AMainPlayer::OnMaxManaChange);
	}

	if (PlayerAttributeSet)
	{
		PlayerAttributeSet->SetMana(50.0f);

		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD());
			if (HUD && HUD->ResourceWidget && HUD->ResourceWidget->GetClass()->ImplementsInterface(UPlayerResource::StaticClass()))
			{
				IPlayerResource::Execute_UpdateMaxMana(HUD->ResourceWidget, PlayerAttributeSet->GetMaxMana());
				IPlayerResource::Execute_UpdateCurrentMana(HUD->ResourceWidget, PlayerAttributeSet->GetMana());
			}
		}
	}
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerAttributeSet)
	{
		FString ManaString = FString::Printf(TEXT("%.1f/%.1f"), PlayerAttributeSet->GetMana(), PlayerAttributeSet->GetMaxMana());
		DrawDebugString(GetWorld(), GetActorLocation(), ManaString, nullptr, FColor::White, 0, true);
	}
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//if (EnhancedInput)
	//{
	//	OnAbility1Press();
	//}
}

void AMainPlayer::OnManaChange(const FOnAttributeChangeData& InData)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD());

	if (HUD && HUD->ResourceWidget)
	{
		if (HUD->ResourceWidget->GetClass()->ImplementsInterface(UPlayerResource::StaticClass()))
		{
			IPlayerResource::Execute_UpdateCurrentMana(HUD->ResourceWidget, InData.NewValue);
		}
	}
}

void AMainPlayer::OnMaxManaChange(const FOnAttributeChangeData& InData)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	AMainHUD* HUD = Cast<AMainHUD>(PC->GetHUD());

	if (HUD && HUD->ResourceWidget)
	{
		if (HUD->ResourceWidget->GetClass()->ImplementsInterface(UPlayerResource::StaticClass()))
		{
			IPlayerResource::Execute_UpdateMaxMana(HUD->ResourceWidget, InData.NewValue);
		}
	}
}

