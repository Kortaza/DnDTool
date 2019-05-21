// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharController.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/Globals.h"

#include "Engine.h"

void APlayableCharController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;	// Show the Mouse at all times

	// Set basic variables
	CameraZoomMuliplier = 20.0f;
	MinCameraDistance = 200.0f;
	MaxCameraDistance = 2000.0f;

	// Set up character and camera pawns for easy access
	CharacterPawn = Cast<APlayableCharacter>(GetPawn());
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
	InputComponent->BindAxis("Camera_MovementForward", this, &APlayableCharController::Camera_MovementForward);
	InputComponent->BindAxis("Camera_MovementRight", this, &APlayableCharController::Camera_MovementRight);
	InputComponent->BindAxis("Camera_Zoom", this, &APlayableCharController::Camera_Zoom);
	InputComponent->BindAxis("Editor_Paint", this, &APlayableCharController::Editor_Paint);
}

//
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

//
void APlayableCharController::Camera_MovementForward(float AxisValue)
{
	CameraPawn->SetMovement(AxisValue * FVector(1.0f, 0.0f, 0.0f));
}

//
void APlayableCharController::Camera_MovementRight(float AxisValue)
{
	CameraPawn->SetMovement(AxisValue * FVector(0.0f, 1.0f, 0.0f));
}

//
void APlayableCharController::Camera_Zoom(float AxisValue)
{
	if (FMath::Abs(AxisValue) > 0.1f)
	{
		float Delta = AxisValue * CameraZoomMuliplier;
		CameraPawn->SpringArm->TargetArmLength = FMath::Clamp(CameraPawn->SpringArm->TargetArmLength + Delta, MinCameraDistance, MaxCameraDistance);
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::FString(FString::SanitizeFloat(CameraPawn->SpringArm->TargetArmLength)));
	}
}

void APlayableCharController::Editor_Paint(float AxisValue)
{

}

//
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