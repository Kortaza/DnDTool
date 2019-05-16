// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharController.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/Globals.h"

void APlayableCharController::BeginPlay()
{
	bShowMouseCursor = true;	// Show the Mouse at all times


}

void APlayableCharController::MouseClickMovement()
{
	FVector MousePos, MouseDir;
	DeprojectMousePositionToWorld(MousePos, MouseDir);

	UWorld* world = GetWorld();
	if (world)
	{
		FHitResult HitResult;
		if (world->LineTraceSingleByChannel(HitResult, MousePos, MousePos + (MouseDir * 10000.0f), ECC_Navigation))
		{
			CameraPawn->SetMovement(LocateTileCenter(HitResult.Location));
		}
	}
}

FVector APlayableCharController::LocateTileCenter(FVector ClickPos)
{
	float ModX, ModY;
	UKismetMathLibrary::FMod(ClickPos.X, Globals::GridSize, ModX);
	UKismetMathLibrary::FMod(ClickPos.Y, Globals::GridSize, ModY);
	FVector TileOrigin = FVector(ClickPos.X - ModX, ClickPos.Y - ModY, ClickPos.Z);
	
	float OffsetX, OffsetY;
	OffsetX = UKismetMathLibrary::SignOfFloat(ClickPos.X) * (Globals::GridSize * 0.5f);
	OffsetY = UKismetMathLibrary::SignOfFloat(ClickPos.Y) * (Globals::GridSize * 0.5f);
	FVector TileOffset = 
}


