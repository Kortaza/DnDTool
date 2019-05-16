// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "CameraPawn.generated.h"

UCLASS()
class DND_TOOL_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ACameraPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetMovement(FVector MoveDir);

protected:
	virtual void BeginPlay() override;

// VARIABLES
public:
	// Viewport/Blueprint Components
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USceneComponent* Origin;
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		UCameraComponent* Camera;

protected:
	float Speed;
	FVector MovementDirection;
	
};
