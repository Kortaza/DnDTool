// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharController.h"
#include "System/Globals.h"
#include "Actors/Environment/Navigatable/Ground.h"
#include "DnD_ToolGameModeBase.h"

#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"


#include "Engine.h"

APlayableCharController::APlayableCharController(const FObjectInitializer& ObjectInitializer)
{
	//static ConstructorHelpers::FObjectFinder<UTexture2D> Texture2D(TEXT("Texture2D'/Game/Materials/Textures/BasicGrass.BasicGrass'"));
	//Tex_BasicGrass = Texture2D.Object;
}

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
	}
}

void APlayableCharController::Editor_Paint(float AxisValue)
{
	if (AxisValue == 1.0f)
	{
		if (TextureEditorFlipFlop == true)
		{
			ADnD_ToolGameModeBase* GameMode = Cast<ADnD_ToolGameModeBase>(UGameplayStatics::GetGameMode(this));
			if (GameMode)
			{
				FHitResult HitResult;
				if (GameMode->ComplexNavigationTraceFromMouse(this, HitResult, Globals::LineTraceLength))
				{
					AGround* Ground = Cast<AGround>(HitResult.Actor);
					if (Ground)
					{
						FVector2D DrawLocation;
						UGameplayStatics::FindCollisionUV(HitResult, 0, DrawLocation);

						FVector GroundScale = Ground->GetActorScale3D();
						FVector2D UVClosestGrid = FVector2D(DrawLocation.X * GroundScale.X, DrawLocation.Y * GroundScale.Y);
						UVClosestGrid = FVector2D(FMath::FloorToInt(UVClosestGrid.X), FMath::FloorToInt(UVClosestGrid.Y));
						UVClosestGrid = FVector2D(UVClosestGrid.X / GroundScale.X, UVClosestGrid.Y / GroundScale.Y);

						if (LastTileEdited != UVClosestGrid)
						{
							Ground->DrawBrush(Tex_BasicGrass, Globals::GridSize, UVClosestGrid);
							LastTileEdited = UVClosestGrid;
						}
					}
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "GameMode not found");
			}
		}
	}
	else
	{
		LastTileEdited = FVector2D(-1.0f, -1.0f);
	}
	TextureEditorFlipFlop = !TextureEditorFlipFlop;
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