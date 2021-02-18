// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Minimap.h"
#include "Components/WidgetComponent.h"

#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AInGameHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> MinimapWidgetClass;

private:
	UMinimap* minimap;
};
