// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharController.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/Globals.h"

void APlayableCharController::BeginPlay()
{
	bShowMouseCursor = true;	// Show the Mouse at all times

	CharacterPawn = (APlayableCharacter*)GetPawn();

	UWorld* world = GetWorld();
	if (world)
	{
		CameraPawn = world->SpawnActor<ACameraPawn>(CharacterPawn->GetActorLocation(), CharacterPawn->GetActorRotation());
		SetViewTargetWithBlend(CameraPawn);
	}
}

void APlayableCharController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseClick", IE_Pressed , this, &APlayableCharController::MouseClickMovement);
	InputComponent->BindAxis("Movement_Forward", this, &APlayableCharController::CameraMovement_Forward);
	InputComponent->BindAxis("Movement_Right", this, &APlayableCharController::CameraMovement_Right);
}

void APlayableCharController::MouseClickMovement()
{
	// Find the Mouse 3D position and direction from the screen
	FVector MousePos, MouseDir;
	DeprojectMousePositionToWorld(MousePos, MouseDir);

	UWorld* world = GetWorld();
	if (world)
	{
		// Raycast from the screen position onto the game world
		FHitResult HitResult;
		if (world->LineTraceSingleByChannel(HitResult, MousePos, MousePos + (MouseDir * 10000.0f), ECC_Navigation))
		{
			// 
			CharacterPawn->StartMovement(LocateTileCenter(HitResult.Location));
		}
	}
}

FVector APlayableCharController::LocateTileCenter(FVector ClickPos)
{
	// Find the clicked tile and the origin point (bottom left corner) 
	float ModX, ModY;
	UKismetMathLibrary::FMod(ClickPos.X, Globals::GridSize, ModX);
	UKismetMathLibrary::FMod(ClickPos.Y, Globals::GridSize, ModY);
	FVector TileOrigin = FVector(ClickPos.X - ModX, ClickPos.Y - ModY, ClickPos.Z);

	// Calculate the offset to get the center of the tile
	float OffsetX, OffsetY;
	OffsetX = UKismetMathLibrary::SignOfFloat(ClickPos.X) * (Globals::GridSize * 0.5f);	// Using sign to account for negative values
	OffsetY = UKismetMathLibrary::SignOfFloat(ClickPos.Y) * (Globals::GridSize * 0.5f);	// Using sign to account for negative values
	FVector TileOffset = FVector(OffsetX, OffsetY, 0.0f);

	return (TileOrigin + TileOffset);
}

//
void APlayableCharController::CameraMovement_Forward(float AxisValue)
{
	CameraPawn->SetMovement(AxisValue * FVector(1.0f, 0.0f, 0.0f));
}

//
void APlayableCharController::CameraMovement_Right(float AxisValue)
{
	CameraPawn->SetMovement(AxisValue * FVector(0.0f, 1.0f, 0.0f));
}
