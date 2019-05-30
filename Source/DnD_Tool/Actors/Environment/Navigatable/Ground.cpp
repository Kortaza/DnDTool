// Fill out your copyright notice in the Description page of Project Settings.

#include "Ground.h"
#include "System/Globals.h"

#include "Engine.h"

int AGround::NextTileID = 1;

// Sets default values
AGround::AGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	Origin->SetupAttachment(RootComponent);

	GroundPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundPlane"));
	GroundPlane->SetupAttachment(Origin);
	GroundPlane->SetRelativeScale3D(FVector(Globals::GridSize / 100.0f));
	GroundPlane->SetRelativeLocation(FVector(Globals::GridSize * 0.5f, Globals::GridSize * 0.5f, 0.0f));
}

// Called every frame
void AGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AGround::BeginPlay()
{
	Super::BeginPlay();
	
	FVector Scale = GetActorScale3D();
	FVector PixelSize = Scale * Globals::GridSize;
	RenderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(this, PixelSize.X, PixelSize.Y);
	UKismetRenderingLibrary::ClearRenderTarget2D(this, RenderTarget, FLinearColor::White);
	
	Mat_Canvas = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, MatInterface_Canvas);
	Mat_Canvas->SetTextureParameterValue("RenderTarget", RenderTarget);
	GroundPlane->SetMaterial(0, Mat_Canvas);

	Mat_Brush = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, MatInterface_Brush);

	// Create the Vector of Tiles
	// TODO: Delete the vectors first and have save/load
	TileBounds = FIntPoint(Scale.X, Scale.Y);
	for (int Row = 0; Row < Scale.X; Row++)
	{
		std::vector<FNavigatableTile*>* TempVector = new std::vector<FNavigatableTile*>();
		Tiles.push_back(TempVector);
		for (int Col = 0; Col < Scale.Y; Col++)
		{
			FNavigatableTile* TempTile = new FNavigatableTile();
			TempTile->ID = NextTileID++;
			TempTile->Index = FIntPoint(Row, Col);

			FVector GroundOrigin = GetActorLocation();
			FVector CentreWorldLoc;
			CentreWorldLoc.X = ((float)Row + 0.5f) * Globals::GridSize + GroundOrigin.X;
			CentreWorldLoc.Y = ((float)Col + 0.5f) * Globals::GridSize + GroundOrigin.Y;
			CentreWorldLoc.Z = GroundOrigin.Z;
			TempTile->CentreWorldLocation = CentreWorldLoc;

			Tiles[Row]->push_back(TempTile);
		}
	}
}

void AGround::DrawBrush(UTexture2D* BrushTexture, float BrushSize, FVector2D DrawLocation)
{
	Mat_Brush->SetTextureParameterValue("BrushTexture", BrushTexture);

	UCanvas* Canvas;
	FVector2D CanvasSize;
	FDrawToRenderTargetContext CanvasContext;

	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(this, RenderTarget, Canvas, CanvasSize, CanvasContext);
	FVector2D ScreenPos = (CanvasSize * DrawLocation);
	Canvas->K2_DrawMaterial(Mat_Brush, ScreenPos, FVector2D(BrushSize, BrushSize), FVector2D(0.0f, 0.0f), FVector2D(1.0f, 1.0f), 90.0f, FVector2D(0.5f, 0.5f));
	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(this, CanvasContext);
}

FNavigatableTile* AGround::FindNavigatableTile(FVector WorldLoc)
{
	FVector Scale = GetActorScale3D();
	FVector Offset = WorldLoc - GetActorLocation();
	
	FIntPoint TileIndex;
	TileIndex.X = FMath::FloorToInt(Offset.X / Globals::GridSize);
	TileIndex.Y = FMath::FloorToInt(Offset.Y / Globals::GridSize);

	FNavigatableTile* NavTile = (*Tiles[TileIndex.X])[TileIndex.Y];

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "X = " + FString::FromInt(TileIndex.X) + "  //  Y = " + FString::FromInt(TileIndex.Y));
	return NavTile;
}

