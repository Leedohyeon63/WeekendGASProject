// EnemyPawn.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "EnemyPawn.generated.h"

class UEnemyAttributeSet;
class UCharacterAttributeSet;
class UWidgetComponent;

UCLASS()
class WEEKENDGASPROJECT_API AEnemyPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AEnemyPawn();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {
		return AbilitySystemComponent;
	};

	UFUNCTION(BlueprintCallable)
	void ChangeHP(float Amount);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	float HPAmount = 0.0f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UWidgetComponent> BarWidgetComponent = nullptr;

private:
	UPROPERTY()
	TObjectPtr<UEnemyAttributeSet> EnemyAttributeSet = nullptr;

	void OnHealthChange(const FOnAttributeChangeData& InData);
	void OnMaxHealthChange(const FOnAttributeChangeData& InData);
};