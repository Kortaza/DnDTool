// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <map>
#include "Actors/Environment/Navigatable/Ground.h"

struct FPathfindingNode
{
	int MovementCost = 10000;
	FNavigatableTile* PreviousNode = NULL;
};

/**
 * 
 */
class DND_TOOL_API Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();

	std::vector<FNavigatableTile*> Start(AGround* Ground, FNavigatableTile* Origin, FNavigatableTile*  Destination);
	
protected:
	bool FindPath();
	bool ValidateTileIndex(FIntPoint NextTileIndex);
	bool AddToOpenList(FNavigatableTile* NewNavTile, FNavigatableTile* CurrentNavTile, int Cos);
	int CalculateCostOfMovement(int RowOffset, int ColOffset);
	std::vector<FNavigatableTile*> CreateOptimalPath();

	// VARIABLES
protected:
	AGround* Ground;
	FNavigatableTile* Origin;
	FNavigatableTile* Destination;
	std::map<unsigned int, FPathfindingNode> PathfindingCostMap;
	std::vector<FNavigatableTile*> ClosedList;
	std::vector<FNavigatableTile*> OpenList;
	bool DoubleDiagonal = false;
};
