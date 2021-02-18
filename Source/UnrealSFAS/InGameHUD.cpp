// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"

AInGameHUD::AInGameHUD()
{
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();
	if(MinimapWidgetClass)
	{
		minimap = CreateWidget<UMinimap>(GetWorld(), MinimapWidgetClass);
		if(minimap)
		{
			UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAA"));
			minimap->AddToViewport();
		}
	}
}

void AInGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
