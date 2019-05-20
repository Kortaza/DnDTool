// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundTile.generated.h"

UCLASS()
class DND_TOOL_API AGroundTile : public AActor
{
	GENERATED_BODY()
	
public:	
	AGroundTile();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// VARIABLES
public:	
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		UStaticMeshComponent* BaseMesh;

	
	
};
