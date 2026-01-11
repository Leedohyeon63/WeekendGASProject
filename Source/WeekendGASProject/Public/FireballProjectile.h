// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "FireballProjectile.generated.h"

UCLASS()
class WEEKENDGASPROJECT_API AFireballProjectile : public AActor
{
	GENERATED_BODY()
	
public:
    AFireballProjectile();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlap(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
    UPROPERTY(VisibleAnywhere, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(VisibleAnywhere, Category = "Collision")
    class USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere, Category = "Visual")
    class UStaticMeshComponent* MeshComp;

    UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true), Category = "GAS")
    FGameplayEffectSpecHandle DamageEffectSpecHandle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
    TSubclassOf<class UGameplayEffect> BurnEffectClass;

};
