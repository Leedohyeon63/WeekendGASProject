// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireballProjectile.generated.h"

UCLASS()
class WEEKENDGASPROJECT_API AFireballProjectile : public AActor
{
	GENERATED_BODY()
	
public:
    AFireballProjectile();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, Category = "Movement")
    class UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(VisibleAnywhere, Category = "Collision")
    class USphereComponent* CollisionComp;

    UPROPERTY(VisibleAnywhere, Category = "Visual")
    class UStaticMeshComponent* MeshComp;

};
