// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "UI/ResourceWidget.h"
#include "Blueprint/UserWidget.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ResourceWidgetClass)
	{
		ResourceWidget = CreateWidget<UResourceWidget>(GetOwningPlayerController(), ResourceWidgetClass);
		if (ResourceWidget)
		{
			ResourceWidget->AddToViewport();
		}
	}
}
