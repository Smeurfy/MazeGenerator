// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealSFAS/MazeGenerator.h"
#include "GameFramework/Actor.h"
#include "MainRoom.generated.h"

UCLASS()
class UNREALSFAS_API AMainRoom : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = MainRoom)
		TSubclassOf<AMazeGenerator> mazeRef;
private:
	int scale;
	
public:	
	// Sets default values for this actor's properties
	AMainRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
