// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Actors/Environment/Navigatable/Ground.h"

struct FPathfindingNode
{
	FIntPoint Location = FIntPoint(0, 0);
	int MovementCost = 10000;
	FPathfindingNode* PreviousNode = NULL;
};

/**
 * 
 */
class DND_TOOL_API Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();

	bool Start(AGround* Ground, FIntPoint Origin, FIntPoint Destination);
	bool FindPath(AGround* Ground);
	bool TraversePath();

protected:
	FPathfindingNode Origin;
	FPathfindingNode Destination;
	std::vector<FPathfindingNode*> ClosedList;
	std::vector<FPathfindingNode*> OpenList;
	std::vector<FPathfindingNode*> OptimalPath;
	bool DoubleDiagonal = false;
};
