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

	UFUNCTION(BlueprintNativeEvent)
		void ChangeGridSize_BPHook(int DimensionX, int DimensionY);

	UFUNCTION(BlueprintCallable)
		void ChangeGridSize(int DimensionX, int DimensionY);

protected:
	virtual void BeginPlay() override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	// VARIABLES
public:	
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USceneComponent* Origin;

	UPROPERTY(EditAnywhere, Category = "Viewport")
		TSubclassOf<AGroundTile> GroundTileParent;
	
protected:
	std::vector< std::vector<AGroundTile*>*> TileArray;
};
