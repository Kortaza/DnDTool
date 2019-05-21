// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPawn.h"
#include "PlayableCharacter.h"

#include "PlayableCharController.generated.h"



/**
 * 
 */
UCLASS()
class DND_TOOL_API APlayableCharController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	

protected:
	// Input Bindings
	virtual void MouseClickMovement();
	virtual void Camera_MovementForward(float AxisValue);
	virtual void Camera_MovementRight(float AxisValue);
	virtual void Camera_Zoom(float AxisValue);
	virtual void Editor_Paint(float AxisValue);

	FVector LocateTileCenter(FVector ClickPos);


	// Variables
public:

protected:
	ACameraPawn* CameraPawn;
	APlayableCharacter* CharacterPawn;

	float CameraZoomMuliplier;
	float MinCameraDistance;
	float MaxCameraDistance;
};
