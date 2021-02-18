// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeGenerator.h"

// Sets default values
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
	CreateGridCells();
	MazeAlgorithm();	
	CreateWalls();
}

// Called every frame
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMazeGenerator::CreateGridCells()
{
	for (int x = 0; x < mazeSize; x++)
	{
		for (int y = 0; y < mazeSize; y++)
		{
			ACell* cell1 = NewObject<ACell>();
			cell1->x = x;
			cell1->y = y;
			gridCells.push_back(cell1);
		}
	}
}

void AMazeGenerator::CreateWalls()
{
	USceneComponent* rootComponent = GetRootComponent();
	FQuat worldRotation(FVector(0.0f, 0.0f, 1.0f), 0.0f);
	FVector posWall;

	//Scale walls based on the cell size
	int wallScale = cellSize / wallMeshCubeDimension;
	FVector worldScale(1, 1, 1);
	FVector mazePositionInWorld = GetTransform().GetTranslation();

	//Calculate the full length of the maze
	float fullLength = cellSize * mazeSize + wallMeshCubeDimension * (mazeSize + 1);
	float halfLength;

	//Calculate the halth length of the maze where for pair mazes is added an offset to center with he door
	if (mazeSize % 2 == 0) {
		halfLength = (cellSize * mazeSize + wallMeshCubeDimension * (mazeSize + 1)) / 2 + cellSize / 2;
	}
	else {
		halfLength = (cellSize * mazeSize + wallMeshCubeDimension * (mazeSize + 1)) / 2 ;
	}
	//Translate maze position to center with the door
	if (northMaze)
		mazePositionInWorld -= FVector(0, halfLength, 0);
	if (eastMaze)
		mazePositionInWorld -= FVector(halfLength, 0, 0);
	if (southMaze)
		mazePositionInWorld -= FVector(fullLength, halfLength, 0);
	if (westMaze)
		mazePositionInWorld -= FVector(halfLength, fullLength, 0);
	
	int distanceBtwCells = cellSize + wallMeshCubeDimension;
	int halfCell = cellSize / 2;
	int wallOffset = halfCell + wallMeshCubeDimension / 2;
	for (ACell* mazeCell : gridCells)
	{
		//Calculate the center position of the cell
		FVector cellCenterPosition(mazeCell->x * distanceBtwCells + mazePositionInWorld.X + halfCell, 
								   mazeCell->y * distanceBtwCells + mazePositionInWorld.Y + halfCell, 
								   5);
	
		for (int i = 0; i < 4; i++)
		{
			if (mazeCell->walls[i] == true) 
			{	
				switch (i)
				{
				case 0: //North
					posWall = cellCenterPosition + FVector(wallOffset, 0, 0);
					worldScale = FVector(1, wallScale + 1, FMath::RandRange(20.f, 50.f));
					break;
				case 1: //East
					posWall = cellCenterPosition + FVector(0, wallOffset, 0);
					worldScale = FVector(wallScale + 1, 1, FMath::RandRange(20.f, 50.f));
					break;
				case 2: //South
					posWall = cellCenterPosition - FVector(wallOffset, 0, 0);
					worldScale = FVector(1, wallScale + 1, FMath::RandRange(20.f, 50.f));
					break;
				case 3: //West
					posWall = cellCenterPosition - FVector(0, wallOffset, 0);
					worldScale = FVector(wallScale + 1, 1, FMath::RandRange(20.f, 50.f));
					break;
				}

				UStaticMeshComponent* meshComponent = NewObject<UStaticMeshComponent>(this);

				FTransform worldXForm(worldRotation, posWall, worldScale);

				meshComponent->SetStaticMesh(WallMesh);
				meshComponent->SetWorldTransform(worldXForm);
				meshComponent->AttachToComponent(rootComponent, FAttachmentTransformRules::KeepWorldTransform);
				meshComponent->RegisterComponent();
			}
		}	
	}
	
}

void AMazeGenerator::MazeAlgorithm()
{
	//Recursive Implementation
	//https://en.wikipedia.org/wiki/Maze_generation_algorithm

	int startingPos = mazeSize / 2;

	//get the index of the middle side cell with (0,0) cell as reference
	if (northMaze)
		startingPos = GetStartingCellIndex(0, mazeSize/2);
	if (eastMaze)
		startingPos = GetStartingCellIndex(mazeSize / 2, 0);
	if (southMaze)
		startingPos = GetStartingCellIndex(mazeSize - 1, mazeSize / 2);
	if (westMaze)
		startingPos = GetStartingCellIndex(mazeSize / 2, mazeSize - 1);
		

	//push starting cell stack
	mazeStack.push(gridCells[startingPos]);
	//Mark cell as visited
	gridCells[startingPos]->visited = true;
	//hack
	gridCells[startingPos]->walls[0] = false;
	gridCells[startingPos]->walls[1] = false;
	gridCells[startingPos]->walls[2] = false;
	gridCells[startingPos]->walls[3] = false;
	
	visitedCells++;

	while (visitedCells < (mazeSize * mazeSize)) {
		std::vector<int> unvisitedNeighbours = GetUnvisitedNeighbours();
		DeleteWalls(unvisitedNeighbours);
	}
}


int AMazeGenerator::GetStartingCellIndex(int a, int b)
{
	return a * mazeSize + b;
}

std::vector<int> AMazeGenerator::GetUnvisitedNeighbours()
{
	std::vector<int> neighbours;

	//North neighbour
	if (mazeStack.top()->x < mazeSize - 1 && GetNeighbour(1, 0)->visited == false) {
		neighbours.push_back(0);
	}
	//East neighbour
	if (mazeStack.top()->y < mazeSize - 1 && GetNeighbour(0, 1)->visited == false) {
		neighbours.push_back(1);
	}
	//South neighbour
	if (mazeStack.top()->x > 0  && GetNeighbour(-1, 0)->visited == false) {
		neighbours.push_back(2);
	}
	//West neighbour
	if (mazeStack.top()->y > 0  && GetNeighbour(0, -1)->visited == false) {
		neighbours.push_back(3);
	}
	return neighbours;
}

ACell* AMazeGenerator::GetNeighbour(int x, int y)
{
	return gridCells[(mazeStack.top()->x + x) * mazeSize + (mazeStack.top()->y + y)];
}

void AMazeGenerator::DeleteWalls(std::vector<int> neighours)
{
	if (!neighours.empty()) {
		//choose random neighbour
		int randNeighbour = neighours[rand() % neighours.size()];
		ACell* nextCell = gridCells[0];
		//Remove walls between top stack and random neighbour
		//mark as visited
		//push new cell to stack
		switch (randNeighbour)
		{
		case 0: //North
			mazeStack.top()->walls[0] = false;
			nextCell = GetNeighbour(1, 0);
			nextCell->walls[2] = false;
			break;
		case 1: //East
			mazeStack.top()->walls[1] = false;
			nextCell = GetNeighbour(0, 1);
			nextCell->walls[3] = false;
			break;
		case 2: //South
			mazeStack.top()->walls[2] = false;
			nextCell = GetNeighbour(-1, 0);
			nextCell->walls[0] = false;
			break;
		case 3: //West
			mazeStack.top()->walls[3] = false;
			nextCell = GetNeighbour(0, -1);
			nextCell->walls[1] = false;
			break;
		}
		visitedCells++;
		nextCell->visited = true;
		mazeStack.push(nextCell);
	}
	else
	{
		//if there are no available neighbours backtrack until you find cell with neighbours
		mazeStack.pop();
	}
}



