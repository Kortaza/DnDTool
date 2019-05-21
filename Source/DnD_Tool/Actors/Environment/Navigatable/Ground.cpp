// Fill out your copyright notice in the Description page of Project Settings.

#include "Ground.h"
#include "System/Globals.h"

#include "Engine.h"


// Sets default values
AGround::AGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	Origin->SetupAttachment(RootComponent);
}

// Called every frame
void AGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AGround::ChangeGridSize(int DimensionX, int DimensionY)
//{
//	while (TileArray.empty() == false)
//	{
//		while (TileArray.back()->empty() == false)
//		{
//			(TileArray.back())->back()->Destroy();
//			(TileArray.back())->pop_back();
//		}
//		TileArray.pop_back();
//	}
//	
//	FVector OriginLoc = GetActorLocation();
//	for (int Col = 0; Col < DimensionX; Col++)
//	{
//		std::vector<AGroundTile*>* tempArray = new std::vector<AGroundTile*>();
//		TileArray.push_back(tempArray);
//		for (int Row = 0; Row < DimensionY; Row++)
//		{
//			FVector Loc = FVector(Col * Globals::GridSize + OriginLoc.X, Row * Globals::GridSize + OriginLoc.Y, OriginLoc.Z);
//			AGroundTile* Tile = GetWorld()->SpawnActor<AGroundTile>(GroundTileParent, Loc, FRotator(0.0f, 0.0f, 0.0f));
//			TileArray[Col]->push_back(Tile);
//		}
//	}
//}

// Called when the game starts or when spawned
void AGround::BeginPlay()
{
	Super::BeginPlay();
	
}

//void AGround::PostEditChangeProperty(struct FPropertyChangedEvent& e)
//{
//	Super::PostEditChangeProperty(e);
//}


