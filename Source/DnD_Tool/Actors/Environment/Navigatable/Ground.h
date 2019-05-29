// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundTile.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"

#include "Ground.generated.h"

UENUM()
enum ETERRAINTEXTURE
{
	EMPTY,
	GRASS,
};

USTRUCT()
struct FNavigatableTile
{
	GENERATED_BODY()

	ETERRAINTEXTURE TerrainTexture = ETERRAINTEXTURE::EMPTY;
	bool DifficultTerrain = false;
	float HeightLevel = 0.0f;
};


UCLASS()
class DND_TOOL_API AGround : public AActor
{
	GENERATED_BODY()
	
public:	
	AGround();
	virtual void Tick(float DeltaTime) override;
	virtual void DrawBrush(UTexture2D* BrushTexture, float BrushSize, FVector2D DrawLocation);

protected:
	virtual void BeginPlay() override;


	// VARIABLES
public:	
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USceneComponent* Origin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport")
		UStaticMeshComponent* GroundPlane;

	UPROPERTY(EditAnywhere, Category = "Texture Editing")
		UMaterialInterface* MatInterface_Canvas;

	UPROPERTY(EditAnywhere, Category = "Texture Editing")
		UMaterialInterface* MatInterface_Brush;


	// 
	std::vector<std::vector<FNavigatableTile*>*> Tiles;
	FIntPoint TileBounds;

protected:
	UTextureRenderTarget2D* RenderTarget;
	UMaterialInstanceDynamic* Mat_Canvas;
	UMaterialInstanceDynamic* Mat_Brush;

	
};
