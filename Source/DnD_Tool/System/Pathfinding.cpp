// Fill out your copyright notice in the Description page of Project Settings.

#include "Pathfinding.h"
#include "Engine.h"

Pathfinding::Pathfinding()
{
}

Pathfinding::~Pathfinding()
{
}

std::vector<FNavigatableTile*> Pathfinding::Start(AGround* Ground, FNavigatableTile* Origin, FNavigatableTile* Destination)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Pathfinding::Start");

	std::vector<FNavigatableTile*> EmptyPath;
	if (Ground == NULL || Origin == NULL || Destination == NULL)
	{
		return EmptyPath;
	}
	this->Ground = Ground;
	this->Origin = Origin;
	this->Destination = Destination;

	DoubleDiagonal = false;

	// Clear previous lists/maps for reuse
	PathfindingCostMap.clear();
	ClosedList.clear();
	OpenList.clear();

	AddToOpenList(Origin, NULL, 0);
	FindPath();

	if (PathfindingCostMap.find(Destination->ID) != PathfindingCostMap.end())
	{
		if (PathfindingCostMap[Destination->ID].PreviousNode != NULL)
		{
			return CreateOptimalPath();
		}
	}

	return EmptyPath;
}

bool Pathfinding::FindPath()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Pathfinding::FindPath");
	if (OpenList.empty() == true)
	{
		// base case to stop recursion
		return false;
	}
	FNavigatableTile* CurrentTile = OpenList[0];
	OpenList.erase(OpenList.begin());
	ClosedList.push_back(CurrentTile);

	for (int RowOffset = -1; RowOffset <= 1; RowOffset++)
	{
		for (int ColOffset = -1; ColOffset <= 1; ColOffset++)
		{
			if ((RowOffset == 0 && ColOffset == 0) == false)
			{			
				FIntPoint TileIndex = FIntPoint(CurrentTile->Index.X + RowOffset, CurrentTile->Index.Y + ColOffset);
				if (ValidateTileIndex(TileIndex))
				{
					// ADD extra code to ensure that the way is clear to move between tiles
					
					FNavigatableTile* NewTile = (*Ground->Tiles[TileIndex.X])[TileIndex.Y];
					AddToOpenList(NewTile, CurrentTile, CalculateCostOfMovement(RowOffset, ColOffset));
				}
			}
		}
	}

	FindPath();

	//REMOVE
	return true;
}

bool Pathfinding::ValidateTileIndex(FIntPoint NextTileIndex)
{
	if (	NextTileIndex.X < 0 || NextTileIndex.X >= Ground->GetActorScale3D().X
		||	NextTileIndex.Y < 0 || NextTileIndex.Y >= Ground->GetActorScale3D().Y)
	{
		return false;
	}
	return true;
}

bool Pathfinding::AddToOpenList(FNavigatableTile* NewNavTile, FNavigatableTile* CurrentNavTile, int Cost)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "Pathfinding::AddToOpenList");
	if (PathfindingCostMap.find(NewNavTile->ID) == PathfindingCostMap.end())
	{
		FPathfindingNode NewNode;
		if (CurrentNavTile)
		{
			NewNode.PreviousNode = CurrentNavTile;
			NewNode.MovementCost = PathfindingCostMap[CurrentNavTile->ID].MovementCost + Cost;
		}
		else
		{
			NewNode.PreviousNode = NULL;
			NewNode.MovementCost = 0;
		}

		PathfindingCostMap[NewNavTile->ID] = NewNode;
		OpenList.push_back(NewNavTile);
		return true;
	}

	if (PathfindingCostMap[CurrentNavTile->ID].MovementCost + Cost < PathfindingCostMap[NewNavTile->ID].MovementCost)
	{
		PathfindingCostMap[NewNavTile->ID].MovementCost = PathfindingCostMap[CurrentNavTile->ID].MovementCost + Cost;
		PathfindingCostMap[NewNavTile->ID].PreviousNode = CurrentNavTile;
	}
	return false;
}

int Pathfinding::CalculateCostOfMovement(int RowOffset, int ColOffset)
{
	int CostOfMovement;
	if (RowOffset == 0 || ColOffset == 0)
	{
		CostOfMovement = 5;
	}
	else
	{
		if (DoubleDiagonal == true)
		{
			CostOfMovement = 10;
		}
		else
		{
			CostOfMovement = 5;
		}
		DoubleDiagonal = !DoubleDiagonal;
	}
	return CostOfMovement;
}

std::vector<FNavigatableTile*> Pathfinding::CreateOptimalPath()
{
	std::vector<FNavigatableTile*> OptimalPath;
	OptimalPath.push_back(Destination);

	int num = 0;
	while (OptimalPath.back()->ID != Origin->ID)
	{
		FString str = FString::FromInt(num) + ":  X :  " + FString::FromInt(OptimalPath.back()->Index.X) + "  //  Y :  " + FString::FromInt(OptimalPath.back()->Index.Y);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, str);
		num++;

		OptimalPath.push_back(PathfindingCostMap[OptimalPath.back()->ID].PreviousNode);
	}
	OptimalPath.pop_back(); // Remove the Origin Node;
	return OptimalPath;
}