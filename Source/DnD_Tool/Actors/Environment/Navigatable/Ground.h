// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundTile.h"
#include "Ground.generated.h"

UCLASS()
class DND_TOOL_API AGround : public AActor
{
	GENERATED_BODY()
	
public:	
	AGround();
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//	void ChangeGridSize(int DimensionX, int DimensionY);

protected:
	virtual void BeginPlay() override;
	//virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	// VARIABLES
public:	
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USceneComponent* Origin;

	UPROPERTY(EditAnywhere, Category = "Viewport")
		TSubclassOf<AGroundTile> GroundTileParent;
	
protected:
	std::vector< std::vector<AGroundTile*>*> TileArray;
};
