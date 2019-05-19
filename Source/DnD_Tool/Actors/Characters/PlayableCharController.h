// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPawn.h"
#include "PlayableCharacter.h"

#include "PlayableCharController.generated.h"

#define ECC_Navigation ECC_GameTraceChannel1

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
	void MouseClickMovement();

protected:
	FVector LocateTileCenter(FVector ClickPos);
	virtual void CameraMovement_Forward(float AxisValue);
	virtual void CameraMovement_Right(float AxisValue);

	// Variables
public:

protected:
	ACameraPawn* CameraPawn;

	UPROPERTY(BlueprintReadWrite, Category = "Pawn")
	APlayableCharacter* CharacterPawn;
};
