// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "TestWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API UTestWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UTestWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;
	
	void UpdateComboCount(int value);

	void ResetCombo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TXTCombo;
};
