// Fill out your copyright notice in the Description page of Project Settings.


#include "AGCNA_FireBall.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AAGCNA_FireBall::AAGCNA_FireBall()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Burn"));
	bAutoDestroyOnRemove = true;	
}

bool AAGCNA_FireBall::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
    UE_LOG(LogTemp, Warning, TEXT("!!! CUE ACTIVE !!! Target: %s"), *GetNameSafe(MyTarget));

    if (SpawnedVFX.IsValid())
    {
        SpawnedVFX->Deactivate();
        SpawnedVFX = nullptr;
    }

    if (MyTarget && BurnVFX)
    {
        SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAttached(
            BurnVFX,
            MyTarget->GetRootComponent(),
            FName("None"),             
            FVector::ZeroVector,          
            FRotator::ZeroRotator,        
            EAttachLocation::SnapToTarget, 
            true                          
        );
        return true;
    }

    if (!BurnVFX)
    {
        UE_LOG(LogTemp, Error, TEXT("BurnVFX is nullptr! Please assign Niagara System in Blueprint."));
    }

    return false;
}

bool AAGCNA_FireBall::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedVFX.IsValid())		// 끝날 때 제거하기
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}
	return true;
}
