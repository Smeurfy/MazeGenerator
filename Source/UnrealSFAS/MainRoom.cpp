// Fill out your copyright notice in the Description page of Project Settings.


#include "MainRoom.h"

// Sets default values
AMainRoom::AMainRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainRoom::BeginPlay()
{
	Super::BeginPlay();
	AMazeGenerator* obj = mazeRef.GetDefaultObject();
	int mazeLength = obj->cellSize * obj->mazeSize + obj->wallMeshCubeDimension * (obj->mazeSize + 1);
	if (mazeLength > 6000)
	{
		//floor size is 2000x2000x200
		scale = mazeLength / 2000;
		//scale main room based on the maze length so it dont overlap
		SetActorScale3D(FVector(scale, scale, 1));
	}
	
}

// Called every frame
void AMainRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

