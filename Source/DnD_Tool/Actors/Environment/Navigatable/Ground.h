// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundTile.h"
#include <vector>
#include "Ground.generated.h"

UCLASS()
class DND_TOOL_API AGround : public AActor
{
	GENERATED_BODY()
	
public:	
	AGround();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	//virtual void OnConstruction(FTransform& Transform) override;

	// VARIABLES
public:	
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USceneComponent* Origin;
	
protected:
	std::vector< std::vector<AGroundTile*>*>* TileArray;
};
