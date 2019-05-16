// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPawn.h"

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
	void MouseClickMovement();
	
protected:
	FVector LocateTileCenter(FVector ClickPos);

	// Variables
public:

protected:
	ACameraPawn* CameraPawn;
};
