// Fill out your copyright notice in the Description page of Project Settings.

#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
}

Pathfinding::~Pathfinding()
{
}

bool Pathfinding::Start(AGround* Ground, FIntPoint Origin, FIntPoint Destination)
{
	this->Origin.Location = Origin;
	this->Origin.MovementCost = 0;
	this->Origin.PreviousNode = NULL;
	this->Destination.Location = Destination;
	this->Destination.MovementCost = 10000;		// Arbitrary large number
	this->Destination.PreviousNode = NULL;

	ClosedList.clear();
	OpenList.clear();
	OptimalPath.clear();

	if (Origin != Destination)
	{
		OpenList.push_back(&this->Origin);
		if (FindPath(Ground))
		{
			TraversePath();
		}
	}

	// REMOVE
	return true;
}

bool Pathfinding::FindPath(AGround* Ground)
{
	if (OpenList.empty() == true)
	{
		// base case to stop recursion
		return false;
	}

	FPathfindingNode* CurrentNode = *(OpenList.begin());
	ClosedList.push_back(CurrentNode);

	if (CurrentNode->Location == Destination.Location)
	{
		Destination.PreviousNode = CurrentNode;
	}


	//REMOVE
	return true;
}

bool Pathfinding::TraversePath()
{
	//REMOVE
	return true;
}