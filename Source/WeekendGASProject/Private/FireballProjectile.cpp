// Fill out your copyright notice in the Description page of Project Settings.


#include "FireballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AFireballProjectile::AFireballProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(15.0f);
    CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
    RootComponent = CollisionComp;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(CollisionComp);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
    ProjectileMovement->InitialSpeed = 1000.0f;
    ProjectileMovement->MaxSpeed = 1000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.0f;

    InitialLifeSpan = 7.0f;
}

// Called when the game starts or when spawned
void AFireballProjectile::BeginPlay()
{
	Super::BeginPlay();

    if (CollisionComp)
    {
        CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AFireballProjectile::OnOverlap);
    }
}

void AFireballProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 나를 쏜 사람이면 무시
    if (OtherActor == GetInstigator()) return;

    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);

    if (TargetASC)
    {
        if (DamageEffectSpecHandle.IsValid())
        {
            TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
        }

        if (BurnEffectClass)
        {
            FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
            ContextHandle.AddSourceObject(this);
            ContextHandle.AddInstigator(GetInstigator(), this);

            FGameplayEffectSpecHandle BurnSpecHandle = TargetASC->MakeOutgoingSpec(BurnEffectClass, 1.0f, ContextHandle);

            if (BurnSpecHandle.IsValid())
            {
                TargetASC->ApplyGameplayEffectSpecToSelf(*BurnSpecHandle.Data.Get());
            }
        }
    }

    Destroy();
}

