// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"
class UResourceWidget;
/**
 * 
 */
UCLASS()
class WEEKENDGASPROJECT_API AMainHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UResourceWidget> ResourceWidgetClass;

	// 실제 화면에 생성된 위젯 인스턴스를 저장하는 변수
	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TObjectPtr<UResourceWidget> ResourceWidget;

protected:
    virtual void BeginPlay() override;
};
