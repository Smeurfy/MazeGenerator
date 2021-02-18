// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <stack>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealSFAS/Cell.h"
#include "DrawDebugHelpers.h"
#include "MazeGenerator.generated.h"


UCLASS()
class UNREALSFAS_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMazeGenerator();
	UPROPERTY(EditDefaultsOnly, Category = Maze)
		UStaticMesh* WallMesh;
	UPROPERTY(EditDefaultsOnly, Category = Maze)
		int wallMeshCubeDimension;
	UPROPERTY(EditDefaultsOnly, Category = Maze)
		int mazeSize;
	UPROPERTY(EditAnywhere, Category = Maze)
		//cell size is the width of the pathway between walls
		int cellSize;
	UPROPERTY(EditAnywhere, Category = Maze)
		bool northMaze;
	UPROPERTY(EditAnywhere, Category = Maze)
		bool eastMaze;
	UPROPERTY(EditAnywhere, Category = Maze)
		bool southMaze;
	UPROPERTY(EditAnywhere, Category = Maze)
		bool westMaze;

	std::vector<ACell*> gridCells;
	std::stack<ACell*> mazeStack;
	int visitedCells = 0;

private:
	void CreateGridCells();
	void CreateWalls();
	void MazeAlgorithm();
	std::vector<int> GetUnvisitedNeighbours();
	ACell* GetNeighbour(int x, int y);
	void DeleteWalls(std::vector<int> neighours);
	int GetStartingCellIndex(int a, int b);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
