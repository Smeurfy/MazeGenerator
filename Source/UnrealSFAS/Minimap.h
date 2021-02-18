// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Minimap.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API UMinimap : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMinimap(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* Minimap;
};
